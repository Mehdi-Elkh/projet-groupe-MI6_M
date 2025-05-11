#include "jeu.h"

//Pour la grille
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

// Pour les matrices

void AfficheMatrice(char piece[TAILLE_PIECE][TAILLE_PIECE]){
    for(int i=0;i<TAILLE_PIECE;i++){
        for(int j=0;j<TAILLE_PIECE;j++){
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

// Fonction pour poser les pièce dans la grille

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
         for (int c = 0; c < COLONNE; c++) {
            grille[l][c] = grille[l-1][c];
        }
    }

    // Une fois toutes les lignes décalées, on vide la première ligne (indice 0)
    for (int c = 0; c < COLONNE; c++) {
        if (c % 2 == 0)
            grille[0][c] = '|';  
        else
            grille[0][c] = ' ';  
    }
}

// Fonction qui détecte et supprime les lignes pleines dans la grille
int SupprimerLignesPleines(char grille[LIGNE][COLONNE]) {
    int cpt = 0;
    for (int i = LIGNE - 1; i >= 0; i--) {
        int pleine = 1;  
        for (int j = 1; j < COLONNE; j += 2) {
            if (grille[i][j] == ' ') {
                pleine = 0;
                break;  
            }
        }

        
        if (pleine) { 
            DecalerLigneVersBas(grille, i);

            i++;
            cpt++;
        }
        
    }
    return cpt*50;
}

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' );
}

int placement_aleatoire(char** piece_joue,int longueur,int hauteur){
    int debordement = 1;
    int colonne_alea = 0;
    while(debordement){
        colonne_alea = (rand()%10)*2+1;
        for(int i=0;i<hauteur;i++){
            for(int j = 0; j < longueur; j++) {
                if (piece_joue[i][j] == '@') {
                    int position_colonne = colonne_alea + 2 * j;
                    if (position_colonne < 0 || position_colonne >= COLONNE) {
                        debordement = 1;
                    }
                    else{
                        debordement = 0;
                    }
                }
            }
        }
    }
    return colonne_alea;
}

void game(Joueur* joueur,int difficulte){
        // Déclaration de la grille
    char grille[LIGNE][COLONNE];
    GrilleDepart(grille,LIGNE,COLONNE);

    // Chargement des pièces
    char pieces[NB_PIECE][TAILLE_PIECE][TAILLE_PIECE];
    ChargementPiece(pieces);
    int tour = 0;
    int scoreP = 0;
    int jeu_en_cours = 1;
    int dernier1 = -1;
    int dernier2 = -1;
    int n = 0;
    struct timespec debut_t,fin_t;
    float temps_lim;
    float temps_fin;
    int rotation_alea;
    int colonne_alea;
    float diff_temps;
    if(difficulte){
        temps_lim = LIM_TEMPS_NORMAL;
        temps_fin = DEBUT_TEMPS_NORMAL;
    }
    else{
        temps_lim = LIM_TEMPS_DUR;
        temps_fin = DEBUT_TEMPS_DUR;
    }
	// "Le jeu "
    while (jeu_en_cours) {
        printf("\033[H\033[2J");
        if(tour>0){
            printf("\nVous avez pris %.2fs a jouer\n\n",diff_temps);
        }

        AfficheGrille(grille, LIGNE, COLONNE);
        
        printf("\nVous avez %.2fs pour jouer\n",temps_fin);

        // Choix de la pièce aléatoire
        int numero_piece = tirer_piece(dernier1,dernier2);
        printf("Voici votre piece :\n");
        AffichePiece(numero_piece,pieces);
	// faut mettree ajour les pièce
	    dernier2 = dernier1;
	    dernier1 = numero_piece;
	    
        // Choix de la rotation
        int angle = -1;
	timespec_get(&debut_t,TIME_UTC);
        do {
            printf("Entrez l'angle de rotation (0, 90, 180, 270) : ");
            if (scanf("%d", &angle) != 1) {
                printf("Entrée invalide ! Veuillez entrer un nombre.\n");
                vider_buffer();
                angle = -1;
                continue;
            }
            vider_buffer();
            if (angle != 0 && angle != 90 && angle != 180 && angle != 270) {
                printf("Angle invalide, veuillez réessayer.\n");
            }
        } while (angle != 0 && angle != 90 && angle != 180 && angle != 270);

        // Appliquer la rotation
        char piece_rotatee[TAILLE_PIECE][TAILLE_PIECE];
        Rotation90(pieces[numero_piece],piece_rotatee,angle/90);
        printf("Voici votre piece après rotation :\n");
        AfficheMatrice(piece_rotatee);

        // Choix de la colonne
        int colonne_choisie = 0;
        int reussite_pose = 0;
        char** piece_joue = NULL;
        int longueur,hauteur;
        piece_joue = Transformation_Piece(piece_rotatee,&longueur,&hauteur);
        
        while (!reussite_pose) {
            printf("Entrez la colonne de placement (0 à 9) : ");
            if (scanf("%d", &colonne_choisie) != 1) {
                printf("Entrée invalide ! Veuillez entrer un nombre.\n");
                vider_buffer();
                continue;
            }
            vider_buffer();

            if (colonne_choisie < 0 || colonne_choisie > 9) {
                printf("Colonne invalide. Veuillez choisir entre 0 et 9.\n");
                continue;
            }
            timespec_get(&fin_t,TIME_UTC);
            diff_temps = (fin_t.tv_sec + fin_t.tv_nsec*pow(10,-9)) - (debut_t.tv_sec + debut_t.tv_nsec*pow(10,-9));
            if(diff_temps<=temps_fin){
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
                    	jeu_en_cours = 0; 
    		        }
    		        else if (n == 1){
    			        reussite_pose = 0;
                    }
                    else{
                       reussite_pose = 1; 
                    }
                }
            }
            else{ // Trop de temps donc aléatoire pièce
                printf("Temps écoulé\n");
                sleep(1);
                rotation_alea = rand()%4;
                Rotation90(pieces[numero_piece],piece_rotatee,rotation_alea);
                free(piece_joue);
                piece_joue = Transformation_Piece(piece_rotatee,&longueur,&hauteur);
                colonne_alea = placement_aleatoire(piece_joue,longueur,hauteur);
                n = PoserPiece(grille, piece_joue,longueur,hauteur, colonne_alea);
                if(n == 0){
                    reussite_pose = 1; 
                	jeu_en_cours = 0; 
		        }
		        else if(n == 1){
			        reussite_pose = 0;
                }
                else{
                    reussite_pose = 1; 
                }
            }
            
        }
        
        if(difficulte){
            if(temps_fin>LIM_TEMPS_NORMAL){
                temps_fin -= 0.2;
            }
        }
        else{
            if(temps_fin>LIM_TEMPS_DUR){
                temps_fin -= 0.2;
            }
        }
        if(jeu_en_cours){
            scoreP += SupprimerLignesPleines(grille); 
        }
        Free_Piece(piece_joue,hauteur);
        tour++;

    }

    joueur->score = scoreP; 
    printf("Partie terminée !\n");
}
