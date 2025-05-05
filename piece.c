#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
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


void ChargementPiece(FILE* f, char liste_matrice[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]) {
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
    if(matrice == NULL){
        printf("La matrice n'existe pas");
        exit(1);
    }
    int cpt=0;
    *longueur = 0;
    *hauteur = 0;
    for(int i=0;i<TAILLE_PIECE;i++){
        cpt = 0;
        for(int j=0;j<TAILLE_PIECE;j++){
            if(matrice[i][j] == '@'){
                cpt ++;
            }
        }
        if(cpt > *longueur){
            *longueur = cpt;
        }
    }
    for(int z=0;z<TAILLE_PIECE;z++){
        cpt = 0;
        for(int y=0;y<TAILLE_PIECE;y++){
            if(matrice[y][z] == '@'){
                cpt ++;
            }
        }
        if(cpt > *hauteur){
            *hauteur = cpt;
        }
    }
    
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

int main() {
    char tab[LIGNE][COLONNE];
    GrilleDepart(tab, LIGNE, COLONNE);
    AfficheGrille(tab, LIGNE, COLONNE);
    FILE* f = NULL;
    f = fopen("piece.txt", "r");
    if(f == NULL){
        printf("Erreur dans l'ouverture du fichier\n");
        printf("code d'erreur = %d \n",errno);
        printf("Message d'erreur = %s \n", strerror(errno));
        exit(1);
    }
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(f, pieces);
    fclose(f);
    AfficheMatrice(pieces[1],5,5);
    char rotation[5][5];
    Rotation90(pieces[1],rotation,1);
    printf("\n");
    AfficheMatrice(rotation,5,5);
    printf("\n\n");
    char** t_piece = NULL;
    int h,l;
    t_piece = Transformation_Piece(rotation,&l,&h);
    Affiche_Matrice_Dynamique(t_piece,l,h);
    Free_Piece(t_piece,h);
    return 0;
}
