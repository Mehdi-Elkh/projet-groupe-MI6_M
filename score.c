#include "score.h"

/**************************************************************
* Ce fichier contient toutes les fonctions liées à la gestion
* du score dans le jeu Tech-Tris.
* Il gère :
*  - L'enregistrement des joueurs.
*  - Le chargement des joueurs dans une liste.
*  - La détection du nombre de joueurs.
*  - Le tri des scores avec l'algorithme du tri fusion.
*  - L'affichage du top 5 des joueurs.
*
* Les fonctions sont écrites de manière robuste avec gestion
* des erreurs d’allocation et de lecture de fichier.
**************************************************************/

void Enregistrement_Score(Joueur joueur){
        //Verifie que le fichier existe
        FILE* fichier = NULL;
        fichier = fopen("score.txt","a");
        if(fichier == NULL){
            printf("Erreur dans l'ouverture du fichier score.txt\n");
            printf("Erreur : %s\n",strerror(errno));
            printf("Code erreur : %d\n",errno);
            exit(1);
        }
        
        // Place le nom du joueur et son score dans le fichier en dessous du joueur precedent
        // On ne fait pas de retour à la ligne si le fichier est vide
        if(ftell(fichier)==0){
            fprintf(fichier,"%s %d",joueur.nom,joueur.score);
        }
        else{
            fprintf(fichier,"\n%s %d",joueur.nom,joueur.score);
        }
        fclose(fichier);
}

int Nombre_Joueur(){
    //Verifie que le fichier existe
    FILE* fichier = NULL;
    fichier = fopen("score.txt","r");
    if(fichier == NULL){
        printf("Erreur dans l'ouverture du fichier score.txt\n");
        printf("Erreur : %s\n",strerror(errno));
        printf("Code erreur : %d\n",errno);
        exit(1);
    }
    char c = ' ';
    int cpt = 0;
    // On compte le nombre de joueur dans le fichier en comptant le nombre de ligne
    while(c != EOF){
        c = fgetc(fichier);
        if(c == '\n'){
            cpt++;
        }
    }
    // Si le fichier est vide, on ne compte qu'il n'y a pas de joueur
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
    // On verifie que le nombre de joueur soit correcte
    n = Nombre_Joueur();
    if(n < 0){
        printf("Erreur dans le Chargement_Score, n doit etre positif\n");
        exit(1);
    }
    //Verifie que le fichier existe
    FILE* fichier = NULL;
    fichier = fopen("score.txt","r");
    if(fichier == NULL){
        printf("Erreur dans l'ouverture du fichier score.txt\n");
        printf("Erreur : %s\n",strerror(errno));
        printf("Code erreur : %d\n",errno);
        exit(1);
    }
    // On alloue la memoire pour le tableau de joueur
    liste_joueur = malloc(n * sizeof(Joueur));
    if(liste_joueur == NULL){
        printf("L'allocation memoire de liste_joueur à echouer ligne 61\n");
        exit(1);
    }
    // On récupère a chaque ligne le nom et le score du joueur pour le mettre dans le tableau
    for(int i=0;i<n;i++){
        fscanf(fichier,"%s %d",liste_joueur[i].nom,&liste_joueur[i].score);
    }
    *taille = n;
    return liste_joueur;
}


// Applique l'alogorithme de tri fusion sur le tableau de joueur
void triFusion(Joueur* liste_joueur,int taille){
    if(liste_joueur == NULL){
        printf("Erreur dans le tri fusion, liste_joueur est NULL\n");
        exit(1);
    }
    if(taille <= 0){
        printf("Erreur dans le tri fusion, taille doit etre superieur à 0\n");
        exit(1);
    }
    triFusionRec(liste_joueur,0,taille-1);
}

void triFusionRec(Joueur* liste_joueur, int debut, int fin){
    int milieu;
    if(debut<fin){
        milieu = (debut+fin)/2;
        triFusionRec(liste_joueur,debut,milieu);
        triFusionRec(liste_joueur,milieu+1,fin);
        fusionner(liste_joueur,debut,milieu,fin);
    }
}

void fusionner(Joueur* liste_joueur, int debut, int milieu, int fin){
    int indexA = debut;
    int indexB = fin;
    Joueur* tab = malloc((fin+1) * sizeof(Joueur));
    if(tab == NULL){
        printf("L'allocation memoire de tab ligne 98 a échoué\n");
        exit(1);
    }
    for(int i=debut;i<milieu+1;i++){
        tab[i] = liste_joueur[i];
    }
    for(int i=milieu+1;i<fin+1;i++){
        tab[i] = liste_joueur[fin-i+milieu+1];
    }
    for(int i=debut;i<fin+1;i++){
        if(tab[indexA].score <= tab[indexB].score){
            liste_joueur[i] = tab[indexA];
            indexA++;
        }
        else{
            liste_joueur[i] = tab[indexB];
            indexB--;
        }
    }
    free(tab);
}



void Croissant_a_Decroissant(Joueur* liste_joueur,int taille){
    // On verifie que les parametres soient corrects
    if(liste_joueur == NULL){
        printf("Erreur dans Croissant_a_Decroissant, liste_joueur est NULL\n");
        exit(1);
    }
    if(taille < 0){
        printf("Erreur dans Croissant_a_Decroissant, taille doit etre positif\n");
        exit(1);
    }
    // On alloue la memoire pour un tableau temporaire
    Joueur* tab = NULL;
    tab = malloc(taille * sizeof(Joueur));
    if(tab == NULL){
        printf("Erreur de l'allocation memoire tab ligne 113\n");
        exit(1);
    }
    //On copie la liste des joueurs dans le tableau temporaire
    for(int i=0;i<taille;i++){
        tab[i] = liste_joueur[i];
    }
    // On met dans l'odre decroissant la liste des joueurs à l'aide du tableau temporaire
    for(int i=0;i<taille;i++){
        liste_joueur[i] = tab[taille-1-i];
    }
    free(tab);
}

void Afficher_Top5(Joueur* liste_joueur,int taille){
    // On verifie que les parametres soient corrects
    if(liste_joueur == NULL){
        printf("Erreur dans l'affichage du top 5, liste_joueur est NULL\n");
        exit(1);
    }
    // On affiche les 5 meilleurs joueurs
    if(taille<5){
        printf("TOP 5\n\n");
        for(int i=0;i<taille;i++){
            printf("%d- %s %d\n",i+1,liste_joueur[i].nom,liste_joueur[i].score);
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

  
