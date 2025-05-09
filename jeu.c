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

int PoserPiece(char grille[LIGNE][COLONNE], char** piece, int longueur, int hauteur, int colonne) {


    // Ligne de départ : tout en haut
    int ligne = 0;

    // vérifier si on peut poser la pièce sur la ligne 0
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < longueur; j++) {
            if (piece[i][j] == '@') {
                int col = colonne + 2 * j;
                int lig = ligne + i; // ligne = 0

                if (lig >= LIGNE || grille[lig][col] == '@') {
                    printf("Erreur : la pièce dépasse en haut de la grille !\n");
                    return 0; // perdu 
                }
            }
        }
    }
    
        // débordement horizontal
    for(int i = 0;i<hauteur;i++){
        for (int j = 0; j < longueur; j++) {
            if (piece[i][j] == '@') {
                int position_colonne = colonne + 2 * j;
                if (position_colonne < 0 || position_colonne >= COLONNE) {
                    printf("Erreur : la pièce dépasse la grille sur les côtés !\n");
                    return 1; 
                }
            }
        }    
    }
    

    // Descendre la pièce jusqu'à collision
    while (1) {
        int collision = 0;

        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < longueur; j++) {
                if (piece[i][j] == '@') {
                    int col = colonne + 2 * j;
                    int lig = ligne + i;

                    // Collision si on touche le bas ou une pièce en dessous
                    if (lig + 1 >= LIGNE || grille[lig + 1][col] == '@') {
                        collision = 1;
                    }
                }
            }
        }

        if (collision) {
            break;
        } else {
            ligne++;
        }
    }

    // Pose réelle
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < longueur; j++) {
            if (piece[i][j] == '@') {
                int col = colonne + 2 * j;
                int lig = ligne + i;
                if (lig >= 0 && lig < LIGNE && col >= 0 && col < COLONNE) {
                    grille[lig][col] = '@';
                }
            }
        }
    }
    return 2; //tout est bien 
}

// Fonction qui décale toutes les lignes de la grille vers le bas à partir d'une ligne donnée
void DecalerLigneVersBas(char grille[LIGNE][COLONNE], int ligne) {
    // On parcourt les lignes de la grille de la ligne donnée jusqu'à la première ligne (en remontant)
    for (int l = ligne; l > 0; l--) {
        // On copie chaque case de la ligne du dessus (l-1) dans la ligne courante (l)
        for (int c = 0; c < COLONNE; c++) {
            grille[l][c] = grille[l-1][c];
        }
    }

    // Une fois toutes les lignes décalées, on vide la première ligne (indice 0)
    for (int c = 0; c < COLONNE; c++) {
        if (c % 2 == 0)
            grille[0][c] = '|';  // Les colonnes paires contiennent les séparateurs '|'
        else
            grille[0][c] = ' ';  // Les colonnes impaires sont vides
    }
}

// Fonction qui détecte et supprime les lignes pleines dans la grille
void SupprimerLignesPleines(char grille[LIGNE][COLONNE]) {
    // On parcourt les lignes de la grille de bas en haut
    for (int i = LIGNE - 1; i >= 0; i--) {
        int pleine = 1;  // On suppose que la ligne est pleine au départ

        // Parcourt uniquement les colonnes impaires (les cases de jeu)
        for (int j = 1; j < COLONNE; j += 2) {
            // Si on trouve une case vide, la ligne n'est pas pleine
            if (grille[i][j] == ' ') {
                pleine = 0;
                break;  // On peut arrêter de vérifier cette ligne
            }
        }

        // Si la ligne est pleine
        if (pleine) {
            // On décale toutes les lignes au-dessus vers le bas à partir de cette ligne
            DecalerLigneVersBas(grille, i);

            // On remonte l'indice i de 1 pour revérifier la même ligne
            // car elle contient maintenant ce qu'il y avait en i-1
            i++;
        }
    }
}

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' );
}



void game(Joueur* joueur){
        // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);

    int scoreP = 0;
    int jeu_en_cours = 1;
    int dernier1 = -1;
    int dernier2 = -1;
    int n = 0;
    while (jeu_en_cours) {
        AfficheGrille(grille, LIGNE, COLONNE);

        // Choix de la pièce aléatoire
        int numero_piece = tirer_piece(dernier1,dernier2);
        printf("Voici votre piece :\n");
        AffichePiece(numero_piece,pieces);
	// faut mettree ajour les pièce
	dernier2 = dernier1;
	dernier1 = numero_piece;
	    
        // Choix de la rotation
        int angle = 0;
        printf("Entrez l'angle de rotation (0, 90, 180, 270) : ");
        scanf("%d", &angle);
        vider_buffer();
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
            vider_buffer();
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
                n = PoserPiece(grille, piece_joue,longueur,hauteur, colonne_choisie);
                if(n == 0){
                    reussite_pose = 1; 
                	jeu_en_cours = 0; // On sort de la boucle
		        }
		        else if (n == 1){
			        reussite_pose = 0;
                }
                else{
                   reussite_pose = 1; 
                }
            }
        }   
        
        SupprimerLignesPleines(grille);
        scoreP += 20;
        free(piece_joue);
	

    }

    joueur->score = scoreP; 
    printf("Partie terminée !\n");
}
