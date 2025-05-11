#include "piece.h"
#include "score.h"
#include "jeu.h"

int main() {
    printf("\033[H\033[2J");
    srand(time(NULL)); 
    printf("            Bienvenue sur Tech-tris            \n\n");
    int choix_Menu, choix_Score, choix_option;
    int menu = 1;
    int menu_score = 1;
    int menu_option = 1;
    char c;
    Joueur joueur;
    Joueur* liste_joueur = NULL;
    char nom_recherche[21];
    int taille_liste_joueur = 0;
    int apparition;
    int score_temp;
    int difficulte = 1; // 1 = normale, 0 = difficile 
                        // Difficulté normale par defaut
    while(menu){
        // Affichage du menu principal
        printf("1- Jouer\n");
        printf("2- Difficulté\n");
        printf("3- Score\n");
        printf("4- Quitter\n\n");
        printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
        do{
            // Lecture du choix de l'utilisateur et verification de la valeur saisie
            scanf("%d",&choix_Menu);
            vider_buffer();
            if(choix_Menu<1 || choix_Menu >4){
                printf("Erreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
                printf("1- Jouer\n");
                printf("2- Difficulté\n");
                printf("3- Score\n");
                printf("4- Quitter\n\n");
                printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
            }
        }while(choix_Menu<1 || choix_Menu >4);
        
        //
        switch(choix_Menu){
            case PARTIE:
                // Demande du pseudo afin de commencer la partie     
                printf("\033[H\033[2J");
                printf("Choisissez un pseudo (maximum 20 caractères): ");
                scanf("%s",joueur.nom);
                vider_buffer();
                printf("\033[H\033[2J");
                //lancement de la partie
                game(&joueur,difficulte);
                //Demande à l'utilisateur s'il souhaite sauvegarder son score et enregistre sa réponse
                printf("Score : %d\n\n",joueur.score);
                printf("Souhaitez-vous sauvegarder le score (o/n) : ");
                do{
                    scanf(" %c",&c);
                    vider_buffer();
                    if(c != 'o' && c != 'O' && c != 'n' && c != 'N'){
                        printf("Erreur dans la saisie\n");
                        printf("Souhaitez-vous sauvegarder le score (o/n) : ");
                    }
                }while(c != 'o' && c != 'O' && c != 'n' && c != 'N');
                
                if(c == 'o' || c == 'O'){
                    // Enregistrement du score dans le fichier score.txt
                    Enregistrement_Score(joueur);
                    printf("\nNom : %s ; Score : %d a bien été enregistré \n",joueur.nom,joueur.score);
                }
                //Affiche le top 5 des meilleurs joueurs
                liste_joueur = Chargement_Score(&taille_liste_joueur);
                triFusion(liste_joueur,taille_liste_joueur);
                Croissant_a_Decroissant(liste_joueur,taille_liste_joueur);
                printf("\nLe top 5 est le suivant : \n\n");
                Afficher_Top5(liste_joueur,taille_liste_joueur);
                free(liste_joueur);
                sleep(4);
                printf("\033[H\033[2J");
                break;


            case OPTION:
                menu_option = 1;
                while(menu_option){
                    // Affichage du menu difficulté
                    printf("\033[H\033[2J");
                    printf("1- Mode normale\n");
                    printf("2- Mode difficile\n");
                    printf("3- Quitter\n");
                    printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                    do{
                        // Lecture du choix de l'utilisateur et verification de la valeur saisie
                        // Choix entre le mode normale et le mode difficile
                        scanf("%d",&choix_option);
                        vider_buffer();
                        if(choix_option<1 || choix_option >3){
                            printf("\nErreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
                            printf("1- Mode normale\n");
                            printf("2- Mode difficile\n");
                            printf("3- Quitter\n");
                            printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                        }
                    }while(choix_option<1 || choix_option >3);
                    switch(choix_option){
                        // Application du mode normale ou difficile
                        case 1:
                            if(difficulte){
                                printf("\nLe mode normale est déjà activé\n");
                                sleep(1);
                            }
                            else{
                                difficulte = 1;
                                printf("\nLe mode normale est activé\n");
                                sleep(1);
                            }
                            break;
                        case 2:
                            if(difficulte){
                                difficulte = 0;
                                printf("\nLe mode difficile est activé\n");
                                sleep(1);
                            }
                            else{
                                printf("\nLe mode difficile est déjà activé\n");
                                sleep(1);
                            }
                            break;
                        case 3:
                            // Quitte le menu difficulté
                            printf("\033[H\033[2J");
                            menu_option = 0;
                            break;
                    }
                }
                break;


            case SCORE:
                printf("\033[H\033[2J");
                menu_score = 1;
                // Chargement de la liste des joueurs et tri de la liste dans l'ordre décroissant
                liste_joueur = Chargement_Score(&taille_liste_joueur);
                triFusion(liste_joueur,taille_liste_joueur);
                Croissant_a_Decroissant(liste_joueur,taille_liste_joueur);
                while(menu_score){
                    // Affichage du menu score
                    printf("1- Afficher le top 5\n");
                    printf("2- Rechercher mon meilleur score\n");
                    printf("3- Quitter\n");
                    printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                    do{
                        // Lecture du choix de l'utilisateur et verification de la valeur saisie
                        scanf("%d",&choix_Score);
                        vider_buffer();
                        if(choix_Score<1 || choix_Score >3){
                            printf("\nErreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
                            printf("1- Afficher le top 5\n");
                            printf("2- Rechercher mon meilleur score\n");
                            printf("3- Quitter\n");
                            printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                        }
                    }while(choix_Score<1 || choix_Score >3);
                    switch(choix_Score){
                        case 1:
                            // Affichage du top 5 des joueurs
                            printf("\n");
                            Afficher_Top5(liste_joueur,taille_liste_joueur);
                            sleep(3);
                            printf("\033[H\033[2J");
                            break;
                        case 2:
                            // Recherche du meilleur score d'un joueur
                            printf("\nEntrez le nom : ");
                            scanf("%s",nom_recherche);
                            vider_buffer();
                            apparition = 0;
                            score_temp = 0;
                            // Compte le nombre d'apparition du joueur dans la liste
                            for(int i=0;i<taille_liste_joueur;i++){
                                if(strcmp(nom_recherche,liste_joueur[i].nom) == 0){
                                    if(score_temp<liste_joueur[i].score){
                                        score_temp = liste_joueur[i].score;
                                    }
                                    apparition++;
                                }
                            }
                            // Si le joueur n'est pas dans la liste, on affiche un message mentionnant qu'il n'a pas de score enregistré
                            if(apparition == 0){
                                printf("\nLe joueur %s n'a pas de score enregistré\n",nom_recherche);
                                sleep(2);
                            }
                            //On affiche le meilleur score du joueur
                            else{
                                printf("\nNom : %s\nMeilleur score : %d\n\n",nom_recherche,score_temp);
                                sleep(3);
                            }
                            printf("\033[H\033[2J");
                            break;
                        case 3:
                            // Quitte le menu score
                            free(liste_joueur);
                            menu_score = 0;
                            printf("\033[H\033[2J");
                            break;
                    }
                }
                break;


            case QUITTER:
                // Quitte le jeu
                menu = 0;
                break;
        }
    }

    printf("\033[H\033[2J");
    printf("Merci d'avoir joué !\n\n");
    return 0;
}
