/*
 * entites.h
 * Header des entités du jeu.
 * - Contient les structs : Joueur, Bulle, Projectile
 * - Contient les prototypes de toutes les fonctions
 *   liées au joueur, aux bulles et aux projectiles
 * - Inclure ce fichier dans tous les autres modules
 */

#ifndef ENTITES_H                /* Protection contre les inclusions en double */
#define ENTITES_H

#define LARGEUR_ECRAN 800        /* Largeur de la fenêtre en pixels */
#define HAUTEUR_ECRAN 600        /* Hauteur de la fenêtre en pixels */
#define VITESSE_JOUEUR 200.0     /* Vitesse du joueur en pixels par seconde */
#define VITESSE_PROJECTILE 400.0 /* Vitesse du projectile en pixels par seconde */
#define MAX_BULLES 20            /* Nombre maximum de bulles simultanées */
#define MAX_PSEUDO 50            /* Longueur maximale du pseudo */
#define MAX_ECLAIRS 5            /* Maximum d'éclairs simultanés */
#define NB_FRAMES_ECLAIR 5       /* Nombre de frames de l'animation éclair */

/* ===== CONSTANTES DU BOSS ===== */
#define VIE_BOSS       5  /* Nombre de coups pour vaincre le boss */
#define NB_ATTACK_BOSS 5  /* Nombre de frames d'attaque du boss */
#define NB_DIE_BOSS    4  /* Nombre de frames de mort du boss */
#define NB_HURT_BOSS   4  /* Nombre de frames de dégâts du boss */
#define NB_IDLE_BOSS   1  /* Nombre de frames idle du boss */

/* ===== ÉTATS DU BOSS ===== */
#define BOSS_IDLE   0  /* Boss immobile */
#define BOSS_ATTACK 1  /* Boss qui attaque */
#define BOSS_HURT   2  /* Boss touché */
#define BOSS_DIE    3  /* Boss mort */

/* ===== STRUCTS ===== */

typedef struct {
    float x, y;   /* Position du joueur en pixels */
    int vivant;   /* 1 = en vie, 0 = mort */
} Joueur;

typedef struct {
    float x, y;   /* Position de la bulle en pixels */
    float vx, vy; /* Vitesse horizontale et verticale */
    int taille;   /* 3=grande, 2=moyenne, 1=petite */
    int actif;    /* 1 = visible, 0 = détruite */
} Bulle;

typedef struct {
    float x, y;  /* Position du projectile en pixels */
    int actif;   /* 1 = tir en cours, 0 = inactif */
} Projectile;

typedef struct {
    float x, y;     /* Position de l'éclair */
    int actif;       /* 1 = visible, 0 = inactif */
    int frame;       /* Compteur d'animation */
} Eclair;

typedef struct {
    float x, y;      /* Position du boss */
    float vx;         /* Vitesse horizontale */
    int vie;          /* Nombre de vies restantes */
    int actif;        /* 1 = vivant, 0 = mort */
    int frame;        /* Compteur d'animation */
    int etat;         /* État actuel du boss */
    int timer_hurt;   /* Timer pour l'état touché */
} Boss;

typedef struct {
    char pseudo[MAX_PSEUDO];  /* Pseudo du joueur */
    int niveau;               /* Numéro du niveau en cours */
    int score;                /* Score actuel */
    float temps;              /* Temps restant */
    Joueur joueur;            /* État du joueur */
    Bulle bulles[MAX_BULLES]; /* Tableau des bulles */
    int nb_bulles;            /* Nombre de bulles actives */
    Projectile proj;          /* Le projectile */
    int frame;                /* Compteur de frames pour les animations */
    int etat_joueur;          /* 0=idle, 1=run, 2=shoot, 3=dead */
    int arme_active;          /* 0 = arme de base, 1 = arme temporaire */
    float arme_timer;         /* Temps restant de l'arme temporaire */
    Eclair eclairs[MAX_ECLAIRS]; /* Tableau des éclairs */
    Boss boss;                /* Le boss du niveau 4 */
} Partie;

/* ===== PROTOTYPES JOUEUR ===== */
Joueur initialiserJoueur(float x, float y);
void deplacerJoueur(Joueur *j, int dir, float dt);

/* ===== PROTOTYPES BULLES ===== */
void ajouterBulle(Bulle *tab, int *nb, float x, float y, int taille);
void mettreAJourBulles(Bulle *tab, int nb, float dt);
void diviserBulle(Bulle *tab, int *nb, int idx);

/* ===== PROTOTYPES PROJECTILE ===== */
void tirer(Joueur *j, Projectile *proj);
void mettreAJourProjectile(Projectile *proj, float dt);

/* ===== PROTOTYPES ECLAIRS ===== */
void lancerEclair(Eclair eclairs[], float x, float y);
void mettreAJourEclairs(Eclair eclairs[], float dt);

/* ===== PROTOTYPES BOSS ===== */
void initialiserBoss(Boss *boss);
void mettreAJourBoss(Boss *boss, float dt);

#endif