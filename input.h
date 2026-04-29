/*
 * input.h
 * Header de la gestion des entrées clavier.
 * - Contient le prototype de lireEntrees()
 * - Gère les déplacements du joueur (flèches gauche/droite)
 * - Gère le tir (espace)
 * - Gère la navigation dans les menus
 * - Inclure ce fichier dans jeu.c
 */
#ifndef INPUT_H       /* Protection contre les inclusions en double */
#define INPUT_H

#include <allegro.h>  /* On a besoin d'Allegro pour les touches clavier */
#include "entites.h"  /* On a besoin de la struct Joueur */

/* Prototypes */
void lireEntrees(Joueur *j, Projectile *p, int *quitter); /* Lit le clavier et met à jour le joueur */

#endif