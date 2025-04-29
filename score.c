#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nom[21];
    int score;
}Joueur;

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

int main()
{
    Joueur j1,j2;
    Joueur tab[2];
    tab[0] = j1;
    tab[1] = j2;
    for(int i=0;i<2;i++){
        printf("Nom : ");
        scanf("%s",tab[i].nom);
        printf("Score : ");
        scanf("%d",&tab[i].score);
        printf("\n");
    }
    Enregistrement_Score(tab[0]);
    Enregistrement_Score(tab[1]);
    return 0;
}
