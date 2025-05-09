#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define COLONNE 21
#define LIGNE 10
#define NB_PIECE 7
#define TAILLE_PIECE 5

typedef enum{PARTIE=1,OPTION,SCORE,QUITTER}Choixmenu;

typedef struct{
    char nom[21];
    int score;
}Joueur;

//fonction_piece :

void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]);
void ChargementPiece(char liste_matrice[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]);
void Rotation90(char piece[TAILLE_PIECE][TAILLE_PIECE],char piece_rota[TAILLE_PIECE][TAILLE_PIECE], int n);
void Taille_Piece(char matrice[TAILLE_PIECE][TAILLE_PIECE],int* longueur, int* hauteur);
char** Transformation_Piece(char piece[TAILLE_PIECE][TAILLE_PIECE],int* longueur, int* hauteur);
void Free_Piece(char** piece,int hauteur);
int tirer_piece(int dernier1, int dernier2);

//fonction_jeu :

void AfficheGrille(char tab[LIGNE][COLONNE], int l, int c);
void AffichePiece(int n, char tab[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE]);
void GrilleDepart(char tab[LIGNE][COLONNE], int l, int c);
void AfficheMatrice(char piece[TAILLE_PIECE][TAILLE_PIECE],int longueur,int hauteur);
void Affiche_Matrice_Dynamique(char** piece,int longueur,int hauteur);
int PoserPiece(char grille[LIGNE][COLONNE], char** piece,int longueur, int hauteur , int colonne);
void DecalerLigneVersBas(char grille[LIGNE][COLONNE], int ligne);
int SupprimerLignesPleines(char grille[LIGNE][COLONNE]);
void vider_buffer();
void game(Joueur* joueur);

//fonction_score :

void Enregistrement_Score(Joueur joueur);
int Nombre_Joueur();
Joueur* Chargement_Score(int* taille);
int partition(Joueur* liste_joueur,int debut,int fin);
void triRapide(Joueur* liste_joueur,int taille);
void triRapideRec(Joueur* liste_joueur, int debut, int fin);
void Croissant_a_Decroissant(Joueur* liste_joueur,int taille);
void Afficher_Top5(Joueur* liste_joueur,int taille);
