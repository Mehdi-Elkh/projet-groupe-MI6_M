#ifndef JEU_H
#define JEU_H

#include "piece.h"
#include "score.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define COLONNE 21
#define LIGNE 10
#define DEBUT_TEMPS_NORMAL 20
#define DEBUT_TEMPS_DUR  12
#define LIM_TEMPS_NORMAL 10
#define LIM_TEMPS_DUR 6

typedef enum{PARTIE=1,OPTION,SCORE,QUITTER}Choixmenu;

void AfficheGrille(char tab[LIGNE][COLONNE], int l, int c);
void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]);
void GrilleDepart(char tab[LIGNE][COLONNE], int l, int c);
void AfficheMatrice(char piece[TAILLE_PIECE][TAILLE_PIECE],int longueur,int hauteur);
void Affiche_Matrice_Dynamique(char** piece,int longueur,int hauteur);
int PoserPiece(char grille[LIGNE][COLONNE], char** piece,int longueur, int hauteur , int colonne);
void DecalerLigneVersBas(char grille[LIGNE][COLONNE], int ligne);
int SupprimerLignesPleines(char grille[LIGNE][COLONNE]);
int placement_aleatoire(char** piece_joue,int hauteur,int longueur);
void vider_buffer();
void game(Joueur* joueur,int difficulté);

#endif
