#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#define COLONNE 21
#define LIGNE 10
#define NB_PIECE 7
#define TAILLE_PIECE 5


void AfficheGrille(char tab[LIGNE][COLONNE], int l, int c) {
    printf(" A B C D E F G H I J\n");
    for(int i = 0; i < l; i++) {
        for(int j = 0; j < c; j++) {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]) {
    for(int i = 0; i < TAILLE_PIECE; i++) {
        for(int j = 0; j < TAILLE_PIECE; j++) {
            printf("%c", tab[n][i][j]);
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


void ChargementPiece(char liste_matrice[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]) {
    FILE* fichier = fopen("piece.txt", "r");
    if (fichier == NULL) {
        printf("Erreur ouverture fichier\n");
        printf("Erreur %d : %s\n", errno, strerror(errno));
        return 1;
    }
    char c;
    for(int m = 0; m < NB_PIECE; m++) {
        for(int i = 0; i < TAILLE_PIECE; i++) {
            do{
                c = fgetc(f);
            }while(c != '@' && c != '.');
            for(int j = 0; j < TAILLE_PIECE; j++) {
                if(c == '.'){
                    liste_matrice[m][i][j] = ' ';
                }
                else{
                    liste_matrice[m][i][j] = c; 
                }
                c = fgetc(f);
            }
        }
    }
    fclose(fichier);
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
        ligne_depart--; // revenir d'un cran parce que on touche l'autre
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
        free(piece_joue);


	// : vérifier si le jeu est perdu (on verra plus tard)
    }

    printf("Partie terminée !\n");

    return 0;
}
