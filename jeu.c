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

// Décale toutes les lignes au-dessus de 'ligne' d'un cran vers le bas,
// puis vide la première ligne
void DecalerLigneVersBas(char grille[LIGNE][COLONNE], int ligne) {
    // 1) Décaler chaque ligne au-dessus de `ligne` vers le bas
    for (int l = ligne; l > 0; l--) {
        for (int c = 0; c < COLONNE; c++) {
            // On copie la case de la ligne l-1 dans la ligne l
            grille[l][c] = grille[l-1][c];
        }
    }
    // 2) Vider la première ligne (l = 0)
    //    On remet les murs '|' aux colonnes paires et des espaces aux impaires
    for (int c = 0; c < COLONNE; c++) {
        if (c % 2 == 0)
            grille[0][c] = '|';
        else
            grille[0][c] = ' ';
    }
}

// Parcourt chaque ligne, détecte celles qui sont pleines et les supprime
void SupprimerLignesPleines(char grille[LIGNE][COLONNE]) {
    for (int i = LIGNE - 1; i >= 0; i--) { // partir du bas et remonter (comme dans un Tetris classique)
        int pleine = 1;
        for (int j = 1; j < COLONNE; j += 2) {  // Les colonnes impaires
            if (grille[i][j] == ' ') {  // Si une colonne est vide
                pleine = 0;
                break;  // Stoppe dès qu'on trouve une case vide
            }
        }
        if (pleine) {
            DecalerLigneVersBas(grille, i);
            i++;  // on remonte pour vérifier la même ligne maintenant décalée
        }
    }
}
/*void partie(Joueur* joueur){
        // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);

    int scoreP = 0;
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
        scoreP += 50;
        free(piece_joue);


	// : vérifier si le jeu est perdu (on verra plus tard)
    }
    joueur->score = scoreP; 
    printf("Partie terminée !\n");
}*/
