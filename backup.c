#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define COLONNE 21
#define LIGNE 10
#define NB_PIECE 7
#define TAILLE_PIECE 5

typedef enum{PARTIE=1,OPTION,SCORE,QUITTER}Choixmenu;

typedef struct{
    char nom[21];
    int score;
}Joueur;

void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]) {
    for(int i = 0; i < TAILLE_PIECE; i++) {
        for(int j = 0; j < TAILLE_PIECE; j++) {
            printf("%c", tab[n][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ChargementPiece(char liste_matrice[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]) {
    FILE* fichier = fopen("piece.txt", "r");
    if (fichier == NULL) {
        printf("Erreur ouverture fichier\n");
        printf("Erreur %d : %s\n", errno, strerror(errno));
        exit(1);
    }
    char c;
    for(int m = 0; m < NB_PIECE; m++) {
        for(int i = 0; i < TAILLE_PIECE; i++) {
            do{
                c = fgetc(fichier);
            }while(c != '@' && c != '.');
            for(int j = 0; j < TAILLE_PIECE; j++) {
                if(c == '.'){
                    liste_matrice[m][i][j] = ' ';
                }
                else{
                    liste_matrice[m][i][j] = c; 
                }
                c = fgetc(fichier);
            }
        }
    }
    fclose(fichier);
}

void Rotation90(char piece[TAILLE_PIECE][TAILLE_PIECE],char piece_rota[TAILLE_PIECE][TAILLE_PIECE], int n){
    if(n==0){
        for(int i=0;i<TAILLE_PIECE;i++){
            for(int j=0;j<TAILLE_PIECE;j++){
                piece_rota[i][j] = piece[i][j];
            }
        }
    }
    else if(n<0 || n>3){
        printf("Erreur dans la saisie de l'entier dans la fonction Rotation90\n");
        exit(1);
    }
    else{
        char tab[TAILLE_PIECE][TAILLE_PIECE];
        for(int i=0;i<TAILLE_PIECE;i++){
            for(int j=0;j<TAILLE_PIECE;j++){
                tab[i][j] = piece[TAILLE_PIECE-1-j][i];
            }
        }
        Rotation90(tab,piece_rota,n-1);
    }
}


void Taille_Piece(char matrice[TAILLE_PIECE][TAILLE_PIECE],int* longueur, int* hauteur){
    int min_l = TAILLE_PIECE, max_l = 0, min_h = TAILLE_PIECE, max_h = 0;
    for(int i = 0;i<TAILLE_PIECE;i++){
        for(int j = 0;j<TAILLE_PIECE;j++){
            if(matrice[i][j] == '@'){
                if(i<min_h){
                    min_h = i;
                }
                if(i>max_h){
                    max_h = i;
                }
                if(j<min_l){
                    min_l = j;
                }
                if(j>max_l){
                    max_l = j;
                }
            }
        }
    }
    *longueur = max_l - min_l + 1;
    *hauteur = max_h - min_h + 1;
    
}

char** Transformation_Piece(char piece[TAILLE_PIECE][TAILLE_PIECE],int* longueur, int* hauteur){
    int l,h,n=0;
    Taille_Piece(piece,&l,&h);
    char** tab = NULL;
    tab = malloc(h*sizeof(char*));
    if(tab == NULL){
        printf("Erreur d'allocation");
        exit(1);
    }
    for(int i=0;i<h;i++){
        tab[i] = malloc(l*sizeof(char));
        if(tab[i] == NULL){
            printf("erreur d'allocation");
            exit(1);
        }
    }
    
    int debut_l=TAILLE_PIECE,debut_h=TAILLE_PIECE;
    for(int i=0;i<TAILLE_PIECE;i++){
        for(int j=0;j<TAILLE_PIECE;j++){
            if(piece[i][j] == '@'){
                if(i<debut_h){
                    debut_h = i;
                }
                if(j<debut_l){
                    debut_l = j;
                }
            }
        }
    }
    
    for(int i=0;i<h;i++){
        for(int j=0;j<l;j++){
            tab[i][j] = piece[debut_h+i][debut_l+j];
        }
    }
    *longueur = l;
    *hauteur = h;
    return tab;
}

int tirer_piece(int dernier1, int dernier2) {
    int n;
    do {
        n = rand() % NB_PIECE;
    } while (n == dernier1 || n == dernier2);
    return n;
}

void Free_Piece(char** piece,int hauteur){
    for(int i=0;i<hauteur;i++){
        free(piece[i]);
    }
    free(piece);
}

void AfficheGrille(char tab[LIGNE][COLONNE], int l, int c) {
    printf(" 0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0; i < l; i++) {
        for(int j = 0; j < c; j++) {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void GrilleDepart(char tab[LIGNE][COLONNE], int l, int c) {
    for(int i = 0; i < LIGNE; i++) {
        for(int j = 0; j < COLONNE; j++) {
            if(j % 2 == 0) {
                tab[i][j] = '|';
            } else {
                tab[i][j] = ' ';
            }
        }
    }
}

void AfficheMatrice(char piece[TAILLE_PIECE][TAILLE_PIECE],int longueur,int hauteur){
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<longueur;j++){
            printf("%c",piece[i][j]);
        }
        printf("\n");
    }
}

void Affiche_Matrice_Dynamique(char** piece,int longueur,int hauteur){
    printf("\n");
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<longueur;j++){
            printf("%c",piece[i][j]);
        }
        printf("\n");
    }
}

void PoserPiece(char grille[LIGNE][COLONNE], char** piece, int longueur, int hauteur, int colonne) {
    // débordement horizontal
    for (int j = 0; j < longueur; j++) {
        if (piece[0][j] == '@') {
            int position_colonne = colonne + 2 * j;
            if (position_colonne < 0 || position_colonne >= COLONNE) {
                printf("Erreur : la pièce dépasse la grille sur les côtés !\n");
                return;
            }
        }
    }

    // Ligne de départ : tout en haut
    int ligne = 0;

    // vérifier si on peut poser la pièce sur la ligne 0
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < longueur; j++) {
            if (piece[i][j] == '@') {
                int col = colonne + 2 * j;
                int lig = ligne + i; // ligne = 0

                if (lig >= LIGNE || grille[lig][col] == '@') {
                    printf("Erreur : la pièce dépasse en haut de la grille ou la grille est pleine !\n");
                    return;
                }
            }
        }
    }

    // Descendre la pièce jusqu'à collision
    while (1) {
        int collision = 0;

        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < longueur; j++) {
                if (piece[i][j] == '@') {
                    int col = colonne + 2 * j;
                    int lig = ligne + i;

                    // Collision si on touche le bas ou une pièce en dessous
                    if (lig + 1 >= LIGNE || grille[lig + 1][col] == '@') {
                        collision = 1;
                    }
                }
            }
        }

        if (collision) {
            break;
        } else {
            ligne++;
        }
    }

    // Pose réelle
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < longueur; j++) {
            if (piece[i][j] == '@') {
                int col = colonne + 2 * j;
                int lig = ligne + i;
                if (lig >= 0 && lig < LIGNE && col >= 0 && col < COLONNE) {
                    grille[lig][col] = '@';
                }
            }
        }
    }
}

// Fonction qui décale toutes les lignes de la grille vers le bas à partir d'une ligne donnée
void DecalerLigneVersBas(char grille[LIGNE][COLONNE], int ligne) {
    // On parcourt les lignes de la grille de la ligne donnée jusqu'à la première ligne (en remontant)
    for (int l = ligne; l > 0; l--) {
        // On copie chaque case de la ligne du dessus (l-1) dans la ligne courante (l)
        for (int c = 0; c < COLONNE; c++) {
            grille[l][c] = grille[l-1][c];
        }
    }

    // Une fois toutes les lignes décalées, on vide la première ligne (indice 0)
    for (int c = 0; c < COLONNE; c++) {
        if (c % 2 == 0)
            grille[0][c] = '|';  // Les colonnes paires contiennent les séparateurs '|'
        else
            grille[0][c] = ' ';  // Les colonnes impaires sont vides
    }
}

// Fonction qui détecte et supprime les lignes pleines dans la grille
void SupprimerLignesPleines(char grille[LIGNE][COLONNE]) {
    // On parcourt les lignes de la grille de bas en haut
    for (int i = LIGNE - 1; i >= 0; i--) {
        int pleine = 1;  // On suppose que la ligne est pleine au départ

        // Parcourt uniquement les colonnes impaires (les cases de jeu)
        for (int j = 1; j < COLONNE; j += 2) {
            // Si on trouve une case vide, la ligne n'est pas pleine
            if (grille[i][j] == ' ') {
                pleine = 0;
                break;  // On peut arrêter de vérifier cette ligne
            }
        }

        // Si la ligne est pleine
        if (pleine) {
            // On décale toutes les lignes au-dessus vers le bas à partir de cette ligne
            DecalerLigneVersBas(grille, i);

            // On remonte l'indice i de 1 pour revérifier la même ligne
            // car elle contient maintenant ce qu'il y avait en i-1
            i++;
        }
    }
}

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' );
}



void game(Joueur* joueur){
        // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);

    int scoreP = 0;
    int jeu_en_cours = 1;
    int dernier1 = -1;
    int dernier2 = -1;
    while (jeu_en_cours) {
        AfficheGrille(grille, LIGNE, COLONNE);

        // Choix de la pièce aléatoire
        int numero_piece = tirer_piece(dernier1,dernier2);
        printf("Voici votre piece :\n");
        AffichePiece(numero_piece,pieces);
	// faut mettree ajour les pièce
	dernier2 = dernier1;
	dernier1 = numero_piece;
	    
        // Choix de la rotation
        int angle = 0;
        printf("Entrez l'angle de rotation (0, 90, 180, 270) : ");
        scanf("%d", &angle);
        vider_buffer();
        // Appliquer la rotation
        char piece_rotatee[TAILLE_PIECE][TAILLE_PIECE];
        Rotation90(pieces[numero_piece],piece_rotatee,angle/90);
        printf("Voici votre piece après rotation :\n");
        AfficheMatrice(piece_rotatee,TAILLE_PIECE,TAILLE_PIECE);

        // Choix de la colonne
        int colonne_choisie = 0;
        int reussite_pose = 0;
        char** piece_joue = NULL;
        int longueur,hauteur;
        piece_joue = Transformation_Piece(piece_rotatee,&longueur,&hauteur);
        while (!reussite_pose) {
            printf("Entrez la colonne de placement (0 à 9) : ");
            scanf("%d", &colonne_choisie);
            vider_buffer();
            colonne_choisie = colonne_choisie * 2 + 1;
        
            // Avant de poser, on vérifie si la colonne est bonne
            int debordement = 0;
            for (int j = 0; j < longueur; j++) {
                if (piece_joue[0][j] == '@') {
                    int position_colonne = colonne_choisie + 2 * j;
                    if (position_colonne < 0 || position_colonne >= COLONNE) {
                        debordement = 1;
                    }
                }
            }
        
            if (debordement) {
                printf("Erreur : la pièce dépasse la grille, choisissez une autre colonne.\n");
            } 
            else {
                PoserPiece(grille, piece_joue,longueur,hauteur, colonne_choisie);
                reussite_pose = 1; // On sort de la boucle
            }
        }
        SupprimerLignesPleines(grille);
        scoreP += 20;
        free(piece_joue);


	// : vérifier si le jeu est perdu (on verra plus tard)
    }
    joueur->score = scoreP; 
    printf("Partie terminée !\n");
}

void Enregistrement_Score(Joueur joueur){
        FILE* fichier = NULL;
        fichier = fopen("score.txt","a");
        if(fichier == NULL){
            printf("Erreur dans l'ouverture du fichier score.txt");
            exit(1);
        }
        
        if(ftell(fichier)==0){
            fprintf(fichier,"%s %d",joueur.nom,joueur.score);
        }
        else{
            fprintf(fichier,"\n%s %d",joueur.nom,joueur.score);
        }
        fclose(fichier);
}

int Nombre_Joueur(){
    FILE* fichier = NULL;
    fichier = fopen("score.txt","r");
    if(fichier == NULL){
        printf("Erreur dans l'ouverture du fichier score.txt");
        exit(1);
    }
    char c = ' ';
    int cpt = 0;
    while(c != EOF){
        c = fgetc(fichier);
        if(c == '\n'){
            cpt++;
        }
    }
    if(ftell(fichier) == 0){
        cpt = 0;
    }
    else{
        cpt++;
    }
    fclose(fichier);
    return cpt;
}


Joueur* Chargement_Score(int* taille){
    Joueur* liste_joueur = NULL;
    int n = 0;
    n = Nombre_Joueur();
    FILE* fichier = NULL;
    fichier = fopen("score.txt","r");
    if(fichier == NULL){
        printf("Erreur dans l'ouverture du fichier score.txt");
        exit(1);
    }
    liste_joueur = malloc(n * sizeof(Joueur));
    if(liste_joueur == NULL){
        printf("L'allocation memoire de liste_joueur à echouer ligne 61");
        exit(1);
    }
    for(int i=0;i<n;i++){
        fscanf(fichier,"%s %d",liste_joueur[i].nom,&liste_joueur[i].score);
    }
    *taille = n;
    return liste_joueur;
}

int partition(Joueur* liste_joueur,int debut,int fin){
    int inf,sup;
    Joueur tmp;
    inf = debut+1;
    sup = fin;
    while(inf<=sup){
        while(liste_joueur[sup].score>liste_joueur[debut].score){
            sup--;
        }
        while(liste_joueur[inf].score<liste_joueur[debut].score){
            inf++;
        }
        if(inf<sup){
            tmp = liste_joueur[sup];
            liste_joueur[sup] = liste_joueur[inf];
            liste_joueur[inf] = tmp;
        }
    }
    tmp = liste_joueur[debut];
    liste_joueur[debut] = liste_joueur[sup];
    liste_joueur[sup] = tmp;
    return sup;
}

void triRapide(Joueur* liste_joueur,int taille){
    triRapideRec(liste_joueur,0,taille-1);
}

void triRapideRec(Joueur* liste_joueur, int debut, int fin){
    int pivot;
    if(debut < fin){
        pivot = partition(liste_joueur,debut,fin);
        triRapideRec(liste_joueur,debut,pivot-1);
        triRapideRec(liste_joueur,pivot+1,fin);
    }
}

void Croissant_a_Decroissant(Joueur* liste_joueur,int taille){
    Joueur* tab = NULL;
    tab = malloc(taille * sizeof(Joueur));
    if(tab == NULL){
        printf("Erreur de l'allocation memoire tab ligne 113");
        exit(1);
    }
    for(int i=0;i<taille;i++){
        tab[i] = liste_joueur[i];
    }
    for(int i=0;i<taille;i++){
        liste_joueur[i] = tab[taille-1-i];
    }
    free(tab);
}

void Afficher_Top5(Joueur* liste_joueur,int taille){
    if(taille<5){
        printf("TOP 5\n\n");
        for(int i=0;i<taille;i++){
            printf("%d- %s %d\n",i,liste_joueur[i].nom,liste_joueur[i].score);
        }
        printf("\n");
    }
    else{
        printf("TOP 5\n\n");
        for(int i=0;i<5;i++){
            printf("%d- %s %d\n",i+1,liste_joueur[i].nom,liste_joueur[i].score);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); 
    printf("            Bienvenue sur Tech-tris            \n\n");
    int choix_Menu, choix_Score;
    int menu = 1;
    int menu_score = 1;
    char c;
    Joueur joueur;
    Joueur* liste_joueur = NULL;
    char nom_recherche[21];
    int taille_liste_joueur = 0;
    int apparition;
    int score_temp;
    while(menu){
        printf("1- Jouer\n");
        printf("2- Difficulté\n");
        printf("3- Score\n");
        printf("4- Quitter\n\n");
        printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
        do{
            scanf("%d",&choix_Menu);
            if(choix_Menu<1 || choix_Menu >4){
                printf("Erreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
                printf("1- Jouer\n");
                printf("2- Difficulté\n");
                printf("3- Score\n");
                printf("4- Quitter\n\n");
                printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
            }
        }while(choix_Menu<1 || choix_Menu >4);
        
        switch(choix_Menu){
            case PARTIE:
                printf("Choisissez un pseudo (maximum 20 caractère): ");
                scanf("%s",joueur.nom);
                vider_buffer();
                game(&joueur);
                printf("Souhaitez-vous sauvegarder le score (o/n) : ");
                do{
                    scanf(" %c",&c);
                    vider_buffer();
                    if(c != 'o' && c != 'O' && c != 'n' && c != 'N'){
                        printf("Erreur dans la saisie\n");
                        printf("Souhaitez-vous sauvegarder le score (o/n) : ");
                    }
                }while(c != 'o' && c != 'O' && c != 'n' && c != 'N');
                
                if(c == 'o' || c == 'O'){
                    Enregistrement_Score(joueur);
                    printf("Nom : %s ; Score : %d a bien été enregistré \n\n",joueur.nom,joueur.score);
                }
                
                break;
            case OPTION:
                printf("L'option n'est pas encore implementer\n");
                break;
            case SCORE:
                menu_score = 1;
                liste_joueur = Chargement_Score(&taille_liste_joueur);
                triRapide(liste_joueur,taille_liste_joueur);
                Croissant_a_Decroissant(liste_joueur,taille_liste_joueur);
                while(menu_score){
                    printf("1- Afficher le top 5\n");
                    printf("2- Rechercher mon meilleur score\n");
                    printf("3- Quitter\n");
                    printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                    do{
                        scanf("%d",&choix_Score);
                        if(choix_Score<1 || choix_Score >3){
                            printf("Erreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
                            printf("1- Afficher le top 5\n");
                            printf("2- Rechercher mon meilleur score\n");
                            printf("3- Quitter\n");
                            printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                        }
                    }while(choix_Score<1 || choix_Score >3);
                    switch(choix_Score){
                        case 1:
                            printf("\n");
                            Afficher_Top5(liste_joueur,taille_liste_joueur);
                            break;
                        case 2:
                            printf("Entrez le nom : ");
                            scanf("%s",nom_recherche);
                            vider_buffer();
                            apparition = 0;
                            score_temp = 0;
                            for(int i=0;i<taille_liste_joueur;i++){
                                if(strcmp(nom_recherche,liste_joueur[i].nom) == 0){
                                    if(score_temp<liste_joueur[i].score){
                                        score_temp = liste_joueur[i].score;
                                    }
                                    apparition++;
                                }
                            }
                            if(apparition == 0){
                                printf("Le joueur %s n'a pas de score enregistré\n",nom_recherche);
                            }
                            else{
                                printf("Nom : %s\nMeilleur score : %d\n\n",nom_recherche,score_temp);
                            }
                            break;
                        case 3:
                            free(liste_joueur);
                            menu_score = 0;
                            break;
                    }
                }
                break;
            case QUITTER:
                printf("Vous avez choisis quitter\n\n");
                menu = 0;
                break;
        }
    }
    printf("Merci d'avoir joué !\n");
    return 0;
}
