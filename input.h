/*
 * input.h
 * Header de la gestion des entrées clavier.
 * - Contient le prototype de lireEntrees()
 * - Gère les déplacements du joueur (flèches gauche/droite)
 * - Gère le tir (espace)
 * - Gère la navigation dans les menus
 * - Inclure ce fichier dans jeu.c
 */

#ifndef INPUT_H
#define INPUT_H

#include <allegro.h> /* Nécessaire pour les constantes clavier */
#include "entites.h" /* Nécessaire pour Joueur et Projectile */

void lireEntrees(Joueur *j, Projectile *proj, int *quitter, float dt); /* Lit le clavier et met à jour le joueur */
void saisirPseudo(char *pseudo);                                        /* Permet au joueur de saisir son pseudo */

#endif