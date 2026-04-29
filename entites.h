/*
 * entites.h
 * Header des entités du jeu.
 * - Contient les structs : Joueur, Bulle, Projectile
 * - Contient les prototypes de toutes les fonctions
 *   liées au joueur, aux bulles et aux projectiles
 * - Inclure ce fichier dans tous les autres modules
 */
#ifndef ENTITES_H   /* Si ENTITES_H n'est pas encore défini... */
#define ENTITES_H   /* ...on le définit pour éviter les inclusions en double */

#define LARGEUR_ECRAN 800       /* Largeur de la fenêtre en pixels */
#define HAUTEUR_ECRAN 600       /* Hauteur de la fenêtre en pixels */
#define VITESSE_JOUEUR 4        /* Nombre de pixels parcourus par le joueur à chaque frame */
#define VITESSE_PROJECTILE 8    /* Nombre de pixels parcourus par le tir à chaque frame */
#define MAX_BULLES 20           /* Nombre maximum de bulles simultanées à l'écran */

/* ---- Structures ---- */

typedef struct {
    float x, y;   /* Position du joueur à l'écran (en pixels) */
    int vivant;   /* 1 = joueur en vie, 0 = joueur mort */
} Joueur;         /* On appelle ce type "Joueur" pour simplifier l'écriture */

typedef struct {
    float x, y;    /* Position de la bulle à l'écran (en pixels) */
    float vx, vy;  /* Vitesse horizontale (vx) et verticale (vy) de la bulle */
    int taille;    /* Taille de la bulle : 3=grande, 2=moyenne, 1=petite */
    int actif;     /* 1 = bulle présente à l'écran, 0 = bulle détruite */
} Bulle;           /* On appelle ce type "Bulle" pour simplifier l'écriture */

typedef struct {
    float x, y;  /* Position du projectile à l'écran (en pixels) */
    int actif;   /* 1 = tir en cours, 0 = pas de tir actif */
} Projectile;    /* On appelle ce type "Projectile" pour simplifier l'écriture */

/* ---- Joueur ---- */
void initialiserJoueur(Joueur *j, float x, float y); /* Place le joueur à la position (x,y) et le met en vie */
void deplacerJoueur(Joueur *j, int direction);        /* Déplace le joueur : -1=gauche, 1=droite */

/* ---- Bulles ---- */
void initialiserBulle(Bulle *b, float x, float y, int taille); /* Crée une bulle à la position (x,y) avec sa taille */
void mettreAJourBulles(Bulle bulles[], int nb);                 /* Met à jour la position de toutes les bulles actives */
void diviserBulle(Bulle bulles[], int idx, int *nb);            /* Divise la bulle en deux plus petites (ou la supprime) */

/* ---- Projectile ---- */
void tirerProjectile(Projectile *p, Joueur *j);  /* Crée un tir à la position du joueur si aucun tir en cours */
void mettreAJourProjectile(Projectile *p);       /* Fait monter le projectile et le désactive s'il sort de l'écran */

#endif  /* Fin de la protection contre les inclusions en double */
