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

#include "entites.h"     /* Pour la struct Partie */
#include "affichage.h"   /* Pour afficher les écrans */
#include "input.h"       /* Pour lire le clavier */
#include "collisions.h"  /* Pour gérer les collisions */
#include "sauvegarde.h"  /* Pour sauvegarder et charger */

#define TEMPS_NIVEAU 60.0  /* Temps imparti par niveau en secondes */
#define NB_NIVEAUX   4     /* Nombre total de niveaux */

Partie initialiserPartie(char *pseudo);              /* Crée une nouvelle partie */
int lancerNiveau(Partie *p, int niveau, BITMAP *buffer); /* Lance un niveau */
void boucleJeu(Partie *p, BITMAP *buffer);           /* Boucle d'enchaînement des niveaux */

#endif