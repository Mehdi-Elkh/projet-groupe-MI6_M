#include "fonction.h"

int main() {
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
    int difficulté = 1;
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
                printf("Choisissez un pseudo (maximum 20 caractères): ");
                scanf("%s",joueur.nom);
                vider_buffer();
                game(&joueur,difficulté);
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
                    printf("Nom : %s ; Score : %d a bien été enregistré \n\n",joueur.nom,joueur.score);
                }
                
                break;
            case OPTION:
                menu_option = 1;
                while(menu_option){
                    printf("1- Mode normale\n");
                    printf("2- Mode difficile\n");
                    printf("3- Quitter\n");
                    printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                    do{
                        scanf("%d",&choix_option);
                        vider_buffer();
                        if(choix_option<1 || choix_option >3){
                            printf("Erreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
                            printf("1- Mode normale\n");
                            printf("2- Mode difficile\n");
                            printf("3- Quitter\n");
                            printf("Que souhaitez-vous faire ? (Entrez le chiffre correspondant) :  ");
                        }
                    }while(choix_option<1 || choix_option >3);
                    switch(choix_option){
                        case 1:
                            if(difficulté){
                                printf("Le mode normale est déjà activé\n");
                            }
                            else{
                                difficulté = 1;
                                printf("Le mode normale est activé\n");
                            }
                            break;
                        case 2:
                            if(difficulté){
                                difficulté = 0;
                                printf("Le mode difficile est activé\n");
                            }
                            else{
                                printf("Le mode difficile est déjà activé\n");
                            }
                            break;
                        case 3:
                            menu_option = 0;
                            break;
                    }
                }
                break;
            case SCORE:
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
                            printf("Erreur, veuillez choisir un chiffre correspondant au proposition si-dessous\n\n");
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
                            break;
                        case 2:
                            printf("Entrez le nom : ");
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
                                printf("Le joueur %s n'a pas de score enregistré\n",nom_recherche);
                            }
                            else{
                                printf("Nom : %s\nMeilleur score : %d\n\n",nom_recherche,score_temp);
                            }
                            break;
                        case 3:
                            free(liste_joueur);
                            menu_score = 0;
                            break;
                    }
                }
                break;
            case QUITTER:
                printf("Vous avez choisi quitter\n\n");
                menu = 0;
                break;
        }
    }
    printf("Merci d'avoir joué !\n");
    return 0;
}
