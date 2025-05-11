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
    int difficulte = 1;
    while(menu){
        printf("1- Jouer\n");
        printf("2- Difficulté\n");
        printf("3- Score\n");
        printf("4- Quitter\n\n");
        printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
        do{
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
        
        switch(choix_Menu){
            case PARTIE:     
                printf("\033[H\033[2J");
                printf("Choisissez un pseudo (maximum 20 caractères): ");
                scanf("%s",joueur.nom);
                vider_buffer();
                printf("\033[H\033[2J");
                game(&joueur,difficulte);
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
                    Enregistrement_Score(joueur);
                    printf("\nNom : %s ; Score : %d a bien été enregistré \n",joueur.nom,joueur.score);
                }
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
                    printf("\033[H\033[2J");
                    printf("1- Mode normale\n");
                    printf("2- Mode difficile\n");
                    printf("3- Quitter\n");
                    printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                    do{
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
                            printf("\033[H\033[2J");
                            menu_option = 0;
                            break;
                    }
                }
                break;
            case SCORE:
                printf("\033[H\033[2J");
                menu_score = 1;
                liste_joueur = Chargement_Score(&taille_liste_joueur);
                triFusion(liste_joueur,taille_liste_joueur);
                Croissant_a_Decroissant(liste_joueur,taille_liste_joueur);
                while(menu_score){
                    printf("1- Afficher le top 5\n");
                    printf("2- Rechercher mon meilleur score\n");
                    printf("3- Quitter\n");
                    printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                    do{
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
                            printf("\n");
                            Afficher_Top5(liste_joueur,taille_liste_joueur);
                            sleep(3);
                            printf("\033[H\033[2J");
                            break;
                        case 2:
                            printf("\nEntrez le nom : ");
                            scanf("%s",nom_recherche);
                            vider_buffer();
                            apparition = 0;
                            score_temp = 0;
                            for(int i=0;i<taille_liste_joueur;i++){
                                if(strcmp(nom_recherche,liste_joueur[i].nom) == 0){
                                    if(score_temp<liste_joueur[i].score){
                                        score_temp = liste_joueur[i].score;
                                    }
                                    apparition++;
                                }
                            }
                            if(apparition == 0){
                                printf("\nLe joueur %s n'a pas de score enregistré\n",nom_recherche);
                                sleep(2);
                            }
                            else{
                                printf("\nNom : %s\nMeilleur score : %d\n\n",nom_recherche,score_temp);
                                sleep(3);
                            }
                            printf("\033[H\033[2J");
                            break;
                        case 3:
                            free(liste_joueur);
                            menu_score = 0;
                            printf("\033[H\033[2J");
                            break;
                    }
                }
                break;
            case QUITTER:
                menu = 0;
                break;
        }
    }
    printf("\033[H\033[2J");
    printf("Merci d'avoir joué !\n\n");
    return 0;
}
