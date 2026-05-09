/*
 * entites.h
 * Header des entités du jeu.
 * - Contient les structs : Joueur, Bulle, Projectile
 * - Contient les prototypes de toutes les fonctions
 *   liées au joueur, aux bulles et aux projectiles
 * - Inclure ce fichier dans tous les autres modules
 */



#ifndef ENTITES_H
#define ENTITES_H

#define LARGEUR_ECRAN 800        /* Largeur de la fenêtre en pixels */
#define HAUTEUR_ECRAN 600        /* Hauteur de la fenêtre en pixels */
#define VITESSE_JOUEUR 200.0     /* Vitesse du joueur en pixels/seconde */
#define VITESSE_PROJECTILE 400.0 /* Vitesse du projectile en pixels/seconde */
#define MAX_BULLES 20            /* Nombre maximum de bulles simultanées */
#define MAX_PSEUDO 50            /* Longueur maximale du pseudo */

typedef struct {
    float x, y;  /* Position du joueur en pixels */
    int vivant;  /* 1 = en vie, 0 = mort */
} Joueur;

typedef struct {
    float x, y;   /* Position de la bulle en pixels */
    float vx, vy; /* Vitesse horizontale et verticale */
    int taille;   /* 3=grande, 2=moyenne, 1=petite */
    int actif;    /* 1 = visible, 0 = détruite */
} Bulle;

typedef struct {
    float x, y; /* Position du projectile en pixels */
    int actif;  /* 1 = tir en cours, 0 = inactif */
} Projectile;

typedef struct {
    char pseudo[MAX_PSEUDO]; /* Pseudo du joueur */
    int niveau;              /* Niveau en cours */
    int score;               /* Score actuel */
    float temps;             /* Temps restant pour le niveau */
    Joueur joueur;           /* État du joueur */
    Bulle bulles[MAX_BULLES]; /* Tableau de toutes les bulles */
    int nb_bulles;            /* Nombre de bulles actives */
    Projectile proj;          /* Le projectile du joueur */
} Partie;

/* ---- Joueur ---- */
Joueur initialiserJoueur(float x, float y);         /* Crée et retourne un joueur placé en (x,y) */
void deplacerJoueur(Joueur *j, int dir, float dt);  /* Déplace le joueur : -1=gauche, 1=droite */

/* ---- Bulles ---- */
void ajouterBulle(Bulle *tab, int *nb, float x, float y, int taille); /* Ajoute une bulle dans le tableau */
void mettreAJourBulles(Bulle *tab, int nb, float dt);                 /* Met à jour toutes les bulles */
void diviserBulle(Bulle *tab, int *nb, int idx);                      /* Divise la bulle idx en deux */

/* ---- Projectile ---- */
void tirer(Joueur *j, Projectile *proj);               /* Crée un tir à la position du joueur */
void mettreAJourProjectile(Projectile *proj, float dt); /* Fait monter le projectile */

#endif