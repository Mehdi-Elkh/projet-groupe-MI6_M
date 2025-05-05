#include <stdlib.h>
#include <stdio.h>
#define COLONNE 21
#define LIGNE 10

void AfficheGrille(char tab[LIGNE][COLONNE],int l,int c){
    printf(" A B C D E F G H I J\n");
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            printf("%c",tab[i][j]);
        }
        printf("\n");
    }
}

void GrilleDepart(char tab[LIGNE][COLONNE],int l,int c){
    for(int i = 0; i < LIGNE; i++){
        for(int j = 0; j < COLONNE; j++){
            if(j%2==0){
                tab[i][j] = '|';
            }
            else{
                tab[i][j] = ' ';
            }
        }
    }
    return;
}

int main(){
    char tab[LIGNE][COLONNE];
    GrilleDepart(tab,LIGNE,COLONNE);
    AfficheGrille(tab,LIGNE,COLONNE);
    return 0;
}
