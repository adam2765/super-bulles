/*
 * jeu.h
 * Header de la logique globale du jeu.
 * - Contient le prototype de initialiserPartie()
 * - Contient le prototype de lancerNiveau()
 * - Contient le prototype de boucleJeu()
 * - Inclure ce fichier dans main.c et jeu.c
 */
#ifndef JEU_H
#define JEU_H

#include "entites.h"    /* Nécessaire pour la struct Partie */
#include "affichage.h"  /* Nécessaire pour afficher les écrans */
#include "input.h"      /* Nécessaire pour lire le clavier */
#include "collisions.h" /* Nécessaire pour gérer les collisions */
#include "sauvegarde.h" /* Nécessaire pour sauvegarder/charger */

#define TEMPS_NIVEAU 60.0  /* Temps imparti par niveau en secondes */
#define NB_NIVEAUX 4       /* Nombre total de niveaux */

Partie initialiserPartie(char *pseudo); /* Crée une nouvelle partie avec le pseudo du joueur */
int lancerNiveau(Partie *p, BITMAP *buffer); /* Lance un niveau, retourne 1=victoire 0=défaite */
void boucleJeu(Partie *p, BITMAP *buffer);   /* Boucle principale du jeu */

#endif