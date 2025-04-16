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

void AfficheMatrice(char piece[TAILLE_PIECE][TAILLE_PIECE]){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%c",piece[i][j]);
        }
        printf("\n");
    }
}

void Rotation90(char piece[TAILLE_PIECE][TAILLE_PIECE], char piece_rota[TAILLE_PIECE][TAILLE_PIECE]){
    for(int i=0;i<TAILLE_PIECE;i++){
        for(int j=0;j<TAILLE_PIECE;j++){
            piece_rota[i][j] = piece[TAILLE_PIECE-1-j][i];
        }
    }
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
    AfficheMatrice(pieces[1]);
    char rotation[5][5];
    Rotation90(pieces[1],rotation);
    AfficheMatrice(rotation);
    return 0;
}
