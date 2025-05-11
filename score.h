#ifndef SCORE_H
#define SCORE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef struct{
    char nom[21];
    int score;
}Joueur;

void Enregistrement_Score(Joueur joueur);
int Nombre_Joueur();
Joueur* Chargement_Score(int* taille);
void triFusion(Joueur* liste_joueur,int taille);
void triFusionRec(Joueur* liste_joueur, int debut, int fin);
void fusionner(Joueur* liste_joueur, int debut, int milieu, int fin);
void Croissant_a_Decroissant(Joueur* liste_joueur,int taille);
void Afficher_Top5(Joueur* liste_joueur,int taille);

#endif
