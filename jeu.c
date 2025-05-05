#include "fonction.h"

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

void DecalerLigneVersBas(char grille[LIGNE][COLONNE], int ligne) {
    for (int l = ligne; l > 0; l--) {
        for (int c = 0; c < COLONNE; c++) {
            grille[l][c] = grille[l-1][c];
        }
    }
    
    for (int c = 0; c < COLONNE; c++) {
        if (c % 2 == 0)
            grille[0][c] = '|';
        else
            grille[0][c] = ' ';
    }
}

void SupprimerLignesPleines(char grille[LIGNE][COLONNE]) {
    for (int i = 0; i < LIGNE; i++) {
        int pleine = 1;
        for (int j = 1; j < COLONNE; j += 2) {  
            if (grille[i][j] == ' ') { 
                pleine = 0;
                break;  
            }
        }
        if (pleine) {
            DecalerLigneVersBas(grille, i);
            i--;  
        }
    }
}
