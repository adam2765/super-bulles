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

#include <allegro.h>  /* Librairie graphique Allegro 4 */
#include "entites.h"  /* Pour la struct Partie */

/* ---- États du joueur ---- */
#define ETAT_IDLE  0  /* Joueur immobile */
#define ETAT_RUN   1  /* Joueur qui court */
#define ETAT_SHOOT 2  /* Joueur qui tire */
#define ETAT_DEAD  3  /* Joueur mort */

/* ---- Fonctions sprites joueur ---- */
void chargerSprites();                              /* Charge les sprites du joueur */
void libererSprites();                              /* Libère les sprites du joueur */

/* ---- Fonctions sprites éclair ---- */
void chargerSpritesEclair();                        /* Charge les sprites de l'éclair */
void libererSpritesEclair();                        /* Libère les sprites de l'éclair */

/* ---- Fonctions sprites boss ---- */
void chargerSpritesBoss();                          /* Charge les sprites du boss */
void libererSpritesBoss();                          /* Libère les sprites du boss */

/* ---- Fonctions d'affichage ---- */
void afficherEcranJeu(BITMAP *buffer, Partie *p);   /* Affiche le jeu en cours */
void afficherMenu(BITMAP *buffer, int option);      /* Affiche le menu principal */
void afficherIntro(BITMAP *buffer);                 /* Affiche l'écran d'intro */
void afficherRegles(BITMAP *buffer);                /* Affiche les règles du jeu */
void afficherVictoire(BITMAP *buffer, int score);   /* Affiche l'écran de victoire */
void afficherDefaite(BITMAP *buffer);               /* Affiche l'écran de défaite */
void afficherDecompte(BITMAP *buffer, int chiffre,int niveau); /* Affiche le décompte 3-2-1 */
void chargerFonds();  /* Charge les fonds de niveau */
void libererFonds();  /* Libère les fonds de niveau */
#endif