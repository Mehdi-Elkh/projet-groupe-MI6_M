#include "fonction.h"

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
