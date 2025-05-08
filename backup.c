#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define COLONNE 21
#define LIGNE 10
#define NB_PIECE 7
#define TAILLE_PIECE 5

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

void PoserPiece(char grille[LIGNE][COLONNE], char** piece,int longueur, int hauteur , int colonne) {
    // Vérification 1 : est-ce que la pièce va déborder ?
    for (int j = 0; j < longueur; j++) {
        if (piece[0][j] == '@') {
            int position_colonne = colonne + 2 * j;
            if (position_colonne < 0 || position_colonne >= COLONNE) {
                printf("Erreur : la pièce dépasse la grille !\n");
                return; // On annule la pose
            }
        }
    }

    // Sinon, on cherche la première ligne libre pour poser la pièce
    int ligne_depart = 0;
    int trouve = 0;

    for (ligne_depart = 0; ligne_depart <= LIGNE - hauteur; ligne_depart++) {
        int collision = 0;
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < longueur; j++) {
                if (piece[i][j] == '@') {
                    int col = colonne + 2 * j;
                    if (grille[ligne_depart + i + 1][col] == '@') {
                        collision = 1;
                    }
                }
            }
        }
        if (collision) {
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        ligne_depart--; 
    } 

    // Pose réelle de la pièce
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < longueur; j++) {
            if (piece[i][j] == '@') {
                int col = colonne + 2 * j;
                if (ligne_depart + i >= 0 && col >= 0 && col < COLONNE) {
                    grille[ligne_depart + i][col] = '@';
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



/*void partie(Joueur* joueur){
        // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);

    int scoreP = 0;
    int jeu_en_cours = 1;
    while (jeu_en_cours) {
        AfficheGrille(grille, LIGNE, COLONNE);

        // Choix de la pièce aléatoire
        int numero_piece = rand() % NB_PIECE;
        printf("Voici votre piece :\n");
        AffichePiece(numero_piece,pieces);

        // Choix de la rotation
        int angle = 0;
        printf("Entrez l'angle de rotation (0, 90, 180, 270) : ");
        scanf("%d", &angle);

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
        scoreP += 50;
        free(piece_joue);


	// : vérifier si le jeu est perdu (on verra plus tard)
    }
    joueur->score = scoreP; 
    printf("Partie terminée !\n");
}*/


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
    srand(time(NULL)); // Pour le hasard

    // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);


    int jeu_en_cours = 1;
    while (jeu_en_cours) {
        AfficheGrille(grille, LIGNE, COLONNE);

        // Choix de la pièce aléatoire
        int numero_piece = rand() % NB_PIECE;
        printf("Voici votre piece :\n");
        AffichePiece(numero_piece,pieces);

        // Choix de la rotation
        int angle = 0;
        printf("Entrez l'angle de rotation (0, 90, 180, 270) : ");
        scanf("%d", &angle);

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
        free(piece_joue);


	// : vérifier si le jeu est perdu (on verra plus tard)
    }

    printf("Partie terminée !\n");

    return 0;
}
