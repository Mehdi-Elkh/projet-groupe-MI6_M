#ifndef PIECE_H
#define PIECE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


#define NB_PIECE 7
#define TAILLE_PIECE 5

void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]);
void ChargementPiece(char liste_matrice[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]);
void Rotation90(char piece[TAILLE_PIECE][TAILLE_PIECE],char piece_rota[TAILLE_PIECE][TAILLE_PIECE], int n);
void Taille_Piece(char matrice[TAILLE_PIECE][TAILLE_PIECE],int* longueur, int* hauteur);
char** Transformation_Piece(char piece[TAILLE_PIECE][TAILLE_PIECE],int* longueur, int* hauteur);
void Free_Piece(char** piece,int hauteur);
int tirer_piece(int dernier1, int dernier2);

#endif