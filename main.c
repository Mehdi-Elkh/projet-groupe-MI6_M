#include "fonction.h"


int main() {
    srand(time(NULL)); // Pour le hasard

    // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);


    int jeu_en_cours = 1;
    while (jeu_en_cours) {
        AfficheGrille(grille, LIGNE, COLONNE);

        // Choix de la pièce aléatoire
        int numero_piece = rand() % NB_PIECE;
        printf("Voici votre piece :\n");
        AffichePiece(numero_piece,pieces);

        // Choix de la rotation
        int angle = 0;
        printf("Entrez l'angle de rotation (0, 90, 180, 270) : ");
        scanf("%d", &angle);

        // Appliquer la rotation
        char piece_rotatee[TAILLE_PIECE][TAILLE_PIECE];
        Rotation90(pieces[numero_piece],piece_rotatee,angle/90);
        printf("Voici votre piece après rotation :\n");
        AfficheMatrice(piece_rotatee,TAILLE_PIECE,TAILLE_PIECE);

        // Choix de la colonne
        int colonne_choisie = 0;
        int reussite_pose = 0;
        char** piece_joue = NULL;
        int longueur,hauteur;
        piece_joue = Transformation_Piece(piece_rotatee,&longueur,&hauteur);
        while (!reussite_pose) {
            printf("Entrez la colonne de placement (0 à 9) : ");
            scanf("%d", &colonne_choisie);
        
            colonne_choisie = colonne_choisie * 2 + 1;
        
            // Avant de poser, on vérifie si la colonne est bonne
            int debordement = 0;
            for (int j = 0; j < longueur; j++) {
                if (piece_joue[0][j] == '@') {
                    int position_colonne = colonne_choisie + 2 * j;
                    if (position_colonne < 0 || position_colonne >= COLONNE) {
                        debordement = 1;
                    }
                }
            }
        
            if (debordement) {
                printf("Erreur : la pièce dépasse la grille, choisissez une autre colonne.\n");
            } 
            else {
                PoserPiece(grille, piece_joue,longueur,hauteur, colonne_choisie);
                reussite_pose = 1; // On sort de la boucle
            }
        }
        SupprimerLignesPleines(grille);
        free(piece_joue);


	// : vérifier si le jeu est perdu (on verra plus tard)
    }

    printf("Partie terminée !\n");

    return 0;
}
