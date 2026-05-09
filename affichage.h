/*
 * affichage.h
 * Header du rendu graphique (Allegro 4).
 * - Contient le prototype de afficherEcranJeu()
 * - Contient le prototype de afficherMenu()
 * - Contient le prototype de afficherVictoire()
 * - Contient le prototype de afficherDefaite()
 * - Inclure ce fichier dans jeu.c et main.c
 */
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <allegro.h> /* Nécessaire pour BITMAP et les fonctions graphiques */
#include "entites.h" /* Nécessaire pour les structs */

void afficherEcranJeu(BITMAP *buffer, Partie *p);          /* Affiche tout le jeu (joueur, bulles, HUD) */
void afficherMenu(BITMAP *buffer, int option);              /* Affiche le menu principal avec option en surbrillance */
void afficherRegles(BITMAP *buffer);                        /* Affiche l'écran des règles du jeu */
void afficherVictoire(BITMAP *buffer, int score);           /* Affiche l'écran de victoire */
void afficherDefaite(BITMAP *buffer);                       /* Affiche l'écran de défaite */
void afficherDecompte(BITMAP *buffer, int chiffre);         /* Affiche le décompte 3-2-1 avant le niveau */

#endif