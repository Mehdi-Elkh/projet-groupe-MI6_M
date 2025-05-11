Projet TECH-TRIS
Ce projet a pour but de recréer le jeu  tétris en C directement dans le terminal.

Fonctionnalités principales
 °Jouer à TECH-TRIS en essayant d’aligner les pièces pour marquer des points.
 °Système de difficulté.
 °Système de score avec enregistrement dans un fichier.
 °Classement automatique des meilleurs joueurs.
 °Recherche d’un score par nom d’utilisateur.
 °Rotation des pièces et gestion des collisions.
 °Chargement des pièces depuis un fichier.

 Organisation de notre Files
  main.c:  Point d’entrée du programme
  jeu.c / jeu.h: Fonctions de gestion de la grille et du jeu
  piece.c / piece.h: Fonctions liées aux pièces (rotation, création, etc.)
  fonction.h: Fonctions utilitaires globales
  piece.txt: Fichier contenant les formes des pièces
  score.txt : Sauvegarde des scores des joueurs
  Makefile:  Pour compiler facilement le projet
  Rapport-techtris.pdf:  Rapport technique du projet


Jeu:
Dès le lancement du programme, un menu principal s’affiche vous permettant de :
  Jouer directement en mode facile,
  Choisir un niveau de difficulté personnalisé,
  Accéder à la section des scores, qui propose deux options :
    Consulter le top 5 des meilleurs joueurs,
    Rechercher votre meilleur score à partir de votre nom d’utilisateur, qui vous sera demandé avant le début de la partie.

Vous pourrez alors jouer et essaye de faire le meilleure score possible
    
    
  









