#include "piece.h"

/**************************************************************
* Ce fichier contient toutes les fonctions liées à la gestion
* des pièces dans le jeu Tech-Tris.
* Il gère :
*  - L'affichage d'une pièce.
*  - Le chargement des pièces depuis le fichier texte.
*  - La rotation des pièces.
*  - La détection de la taille utile d'une pièce.
*  - La transformation d'une pièce en matrice dynamique.
*  - La libération de mémoire des pièces dynamiques.
*  - Le tirage aléatoire d'une pièce différente des deux dernières.
*
* Les fonctions sont écrites de manière robuste avec gestion
* des erreurs d’allocation et de lecture de fichier.
**************************************************************/

// Affiche à l'écran la matrice d'une pièce donnée (sans rotation).
// Sert à montrer la pièce actuelle au joueur avant de choisir sa rotation.
void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]) {
    for(int i = 0; i < TAILLE_PIECE; i++) {
        for(int j = 0; j < TAILLE_PIECE; j++) {
            printf("%c", tab[n][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Charge les pièces depuis le fichier texte "piece.txt" et les stocke
// dans une matrice en remplaçant les '.' par des espaces.
// Vérifie la bonne ouverture du fichier et la validité du contenu.
// Quitte le programme proprement si erreur.
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
                if ( c  == EOF) {
                    printf("Erreur lecture fichier\n");
                    printf("Erreur %d : %s\n", errno, strerror(errno));
                    fclose(fichier);
                    exit(1);
                }
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

// Réalise la rotation d'une pièce selon l'angle souhaité (0, 90, 180, 270°).
// La rotation est effectuée récursivement en tournant de 90° à chaque appel.
// Vérifie la validité de l'angle demandé.
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

// Calcule la hauteur et la longueur minimale occupée par une pièce.
// Utile pour ne conserver que la partie utile de la pièce sans les espaces vides.
// Si aucune case '@' n'est présente, génère une erreur.
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

    if (min_h == TAILLE_PIECE) {
        printf("Erreur : aucune case '@' trouvée dans la pièce pour calculer sa taille.\n");
        exit(1);
    }
    
    *longueur = max_l - min_l + 1;
    *hauteur = max_h - min_h + 1;
    
}

// Transforme une pièce (matrice carrée fixe) en matrice dynamique de taille utile.
// Permet de manipuler des pièces plus petites et économiser de la mémoire.
// Vérifie l’allocation dynamique et s'assure que la pièce contient bien au moins un '@'.
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

    if (debut_h == TAILLE_PIECE && debut_l == TAILLE_PIECE) {
        printf("Erreur : la pièce ne contient aucun '@'\n");
        exit(1);
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

// Tire aléatoirement une pièce parmi celles disponibles, en évitant
// les deux dernières jouées pour garantir de la variété.
// Retourne l'indice de la pièce tirée.
int tirer_piece(int dernier1, int dernier2) {
    int n;
    do {
        n = rand() % NB_PIECE;
    } while (n == dernier1 || n == dernier2);
    return n;
}

// Libère proprement la mémoire allouée dynamiquement pour une pièce.
// Évite les fuites mémoire dans le programme.
void Free_Piece(char** piece,int hauteur){
    if (piece != NULL) {
        for(int i=0;i<hauteur;i++){
            free(piece[i]);
        }
        free(piece);
    }
}
