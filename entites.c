/*
 * entites.c
 * Gestion des entités du jeu (joueur, bulles, projectiles).
 * - Initialiser et déplacer le joueur
 * - Ajouter, mettre à jour et diviser les bulles
 * - Gérer les tirs (créer et déplacer les projectiles)
 * - Gérer la sauvegarde et le chargement des parties
 */
#include "entites.h"  /* On importe les structs et prototypes définis dans entites.h */

/* ===================== JOUEUR ===================== */

void initialiserJoueur(Joueur *j, float x, float y) {  /* Reçoit un pointeur vers le joueur et sa position de départ */
    j->x = x;       /* On place le joueur à la position horizontale x */
    j->y = y;       /* On place le joueur à la position verticale y */
    j->vivant = 1;  /* Le joueur commence en vie (1 = vivant) */
}

void deplacerJoueur(Joueur *j, int direction) {        /* direction vaut -1 (gauche) ou 1 (droite) */
    j->x += direction * VITESSE_JOUEUR;                /* On ajoute ou soustrait la vitesse selon la direction */

    if (j->x < 0) j->x = 0;                           /* Empêche le joueur de sortir par la gauche */
    if (j->x > LARGEUR_ECRAN) j->x = LARGEUR_ECRAN;   /* Empêche le joueur de sortir par la droite */
}

/* ===================== BULLES ===================== */

void initialiserBulle(Bulle *b, float x, float y, int taille) {  /* Reçoit la position et la taille de la bulle à créer */
    b->x = x;        /* Position horizontale de départ de la bulle */
    b->y = y;        /* Position verticale de départ de la bulle */
    b->taille = taille;  /* Taille de la bulle : 3=grande, 2=moyenne, 1=petite */
    b->actif = 1;    /* La bulle est active dès sa création (1 = visible) */
    b->vx = 2.0;     /* Vitesse horizontale initiale (vers la droite) */
    b->vy = -3.0;    /* Vitesse verticale initiale (vers le haut, donc négative) */
}

void mettreAJourBulles(Bulle bulles[], int nb) {   /* Reçoit le tableau de toutes les bulles et leur nombre */
    int i;                                          /* Variable de boucle */
    for (i = 0; i < nb; i++) {                     /* On parcourt toutes les bulles */
        if (!bulles[i].actif) continue;            /* Si la bulle est inactive on la saute */

        bulles[i].x += bulles[i].vx;              /* On déplace la bulle horizontalement selon sa vitesse */
        bulles[i].y += bulles[i].vy;              /* On déplace la bulle verticalement selon sa vitesse */

        if (bulles[i].x <= 0 || bulles[i].x >= LARGEUR_ECRAN)  /* Si la bulle touche un bord gauche ou droit... */
            bulles[i].vx *= -1;                                  /* ...on inverse sa vitesse horizontale (rebond) */

        if (bulles[i].y <= 0)     /* Si la bulle touche le plafond... */
            bulles[i].vy *= -1;   /* ...on inverse sa vitesse verticale (rebond) */

        bulles[i].vy += 0.05;    /* Gravité légère : la bulle accélère doucement vers le bas à chaque frame */
    }
}

void diviserBulle(Bulle bulles[], int idx, int *nb) {  /* idx = indice de la bulle touchée, nb = nombre total de bulles */
    if (bulles[idx].taille <= 1) {  /* Si c'est la plus petite taille... */
        bulles[idx].actif = 0;      /* ...elle disparaît simplement */
        return;                     /* On arrête la fonction ici */
    }

    bulles[idx].actif = 0;  /* La bulle touchée disparaît */

    /* Création de la première bulle fille (part vers la droite) */
    bulles[*nb].x = bulles[idx].x;           /* Même position x que la bulle détruite */
    bulles[*nb].y = bulles[idx].y;           /* Même position y que la bulle détruite */
    bulles[*nb].taille = bulles[idx].taille - 1;  /* Une taille en moins */
    bulles[*nb].vx = 3.0;                    /*Part vers la droite */
    bulles[*nb].vy = -4.0;                   /* Repart vers le haut */
    bulles[*nb].actif = 1;                   /* La nouvelle bulle est active */
    (*nb)++;                                 /* On incrémente le nombre total de bulles */

    /* Création de la deuxième bulle fille (part vers la gauche) */
    bulles[*nb].x = bulles[idx].x;           /* Même position x que la bulle détruite */
    bulles[*nb].y = bulles[idx].y;           /* Même position y que la bulle détruite */
    bulles[*nb].taille = bulles[idx].taille - 1;  /* Une taille en moins */
    bulles[*nb].vx = -3.0;                   /* Part vers la gauche */
    bulles[*nb].vy = -4.0;                   /* Repart vers le haut */
    bulles[*nb].actif = 1;                   /* La nouvelle bulle est active */
    (*nb)++;                                 /* On incrémente à nouveau le nombre total de bulles */
}

/* =================== PROJECTILE =================== */

void tirerProjectile(Projectile *p, Joueur *j) {  /* Reçoit le projectile et le joueur qui tire */
    if (p->actif) return;  /* Si un tir est déjà en cours, on ne peut pas retirer */
    p->x = j->x;           /* Le tir part de la position horizontale du joueur */
    p->y = j->y;           /* Le tir part de la position verticale du joueur */
    p->actif = 1;           /* Le projectile devient actif (visible à l'écran) */
}

void mettreAJourProjectile(Projectile *p) {  /* Reçoit le projectile à mettre à jour */
    if (!p->actif) return;                   /* Si pas de tir en cours, rien à faire */

    p->y -= VITESSE_PROJECTILE;  /* Le projectile monte (y diminue car 0 est en haut) */

    if (p->y < 0)       /* Si le projectile sort par le haut de l'écran... */
        p->actif = 0;   /* ...il disparaît */
}