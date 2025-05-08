#include "fonction.h"

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

  
