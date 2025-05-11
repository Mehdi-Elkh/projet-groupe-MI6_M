Projet TECH-TRIS
Ce projet a pour but de recréer le jeu tétris en C directement dans le terminal.  

- Prérequis :
  - Version du language C : C11 ou ultérieure

1) Fonctionnalités principales :  
 - Jouer à TECH-TRIS en essayant d’aligner les pièces pour marquer des points.  
 - Système de difficulté.  
 - Système de score avec enregistrement dans un fichier.  
 - Classement automatique des meilleurs joueurs.  
 - Recherche d’un score par nom d’utilisateur.  
 - Rotation des pièces et gestion des collisions.  
 - Chargement des pièces depuis un fichier.  

 2) Organisation de notre Files  
  - main.c:  Point d’entrée du programme  
  - jeu.c / jeu.h: Fonctions de gestion de la grille et du jeu  
  - piece.c / piece.h: Fonctions liées aux pièces (rotation, création, etc.)
  - score.c / score.h: Fonctions lié à la gestion du score  
  - piece.txt: Fichier contenant les formes des pièces  
  - score.txt : Sauvegarde des scores des joueurs  
  - Makefile:  Pour compiler facilement le projet  
  - Rapport-techtris.pdf:  Rapport technique du projet  


3) Fonctionnement du jeu:
Dès le lancement du programme, un menu principal s’affiche vous permettant de :  
  - Jouer directement en mode facile,  
  - Choisir un niveau de difficulté facile ou difficile,  
  Accéder à la section des scores, qui propose deux options :  
    - Consulter le top 5 des meilleurs joueurs,  
    - Rechercher votre meilleur score à partir de votre nom d’utilisateur, qui vous sera demandé avant le début de la partie.  

4) Comment jouer :  
- Choisissez une rotation pour la pièce dans le sens horaire.  
- Choisissez une colonne dans laquelle placer la pièce en prenant en compte que ça placera le côté le plus a gauche de la piece dans cette colonne.
- Complétez les lignes afin de gagner des points.
- Jouer avant le temps imparti.  
- Ne dépassez pas le haut de la grille.  

Vous pourrez alors jouer et essaye de faire le meilleure score possible  
    
    
  









