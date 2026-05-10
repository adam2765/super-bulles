/*
 * collision.c
 * Détection et gestion des collisions.
 * - Tester la collision entre deux cercles (tir/bulle)
 * - Tester la collision entre un cercle et un rectangle (bulle/joueur)
 * - Gérer toutes les collisions de la boucle de jeu
 * - Appeler diviserBulle() si collision tir/bulle détectée
 */
#include "collisions.h" /* On importe les prototypes */
#include <math.h>       /* Pour sqrt() */
#include <allegro.h>    /* Pour SCREEN_H */

/* ===== COLLISION ENTRE DEUX CERCLES ===== */
int collisionCercles(float x1, float y1, float r1, float x2, float y2, float r2) {
    float dx = x2 - x1;                   /* Écart horizontal */
    float dy = y2 - y1;                   /* Écart vertical */
    float distance = sqrt(dx*dx + dy*dy); /* Distance entre les centres */
    return distance < (r1 + r2);         /* Vrai si les cercles se touchent */
}

/* ===== COLLISION ENTRE DEUX RECTANGLES ===== */
int collisionRectangles(float x1, float y1, float w1, float h1,
                         float x2, float y2, float w2, float h2) {
    if (x1 + w1 < x2) return 0; /* Rectangle 1 trop à gauche */
    if (x2 + w2 < x1) return 0; /* Rectangle 2 trop à gauche */
    if (y1 + h1 < y2) return 0; /* Rectangle 1 trop en haut */
    if (y2 + h2 < y1) return 0; /* Rectangle 2 trop en haut */
    return 1;                    /* Les rectangles se touchent */
}

/* ===== GÉRER TOUTES LES COLLISIONS ===== */
void gererCollisions(Partie *p) {
    int i;           /* Variable de boucle pour les bulles */
    int j;           /* Variable de boucle pour les éclairs */
    int rayon;       /* Rayon de la bulle */
    int joueur_haut; /* Position haute du joueur */

    joueur_haut = SCREEN_H - 95; /* Haut du joueur */

    /* ===== COLLISIONS AVEC LES BULLES ===== */
    for (i = 0; i < p->nb_bulles; i++) {
        if (!p->bulles[i].actif) continue; /* On saute les bulles détruites */

        rayon = p->bulles[i].taille * 15;  /* Rayon de la bulle */

        /* Collision tir / bulle */
        if (p->proj.actif) {
            if (collisionCercles(
                    p->proj.x, p->proj.y, 5,
                    p->bulles[i].x, p->bulles[i].y, rayon)) {
                p->proj.actif = 0;                         /* Le projectile disparaît */
                diviserBulle(p->bulles, &p->nb_bulles, i); /* La bulle se divise */
                p->score += 100 * p->bulles[i].taille;     /* On gagne des points */
            }
        }

        /* Collision bulle / joueur */
        if (p->joueur.vivant) {
            if (collisionRectangles(
                    p->bulles[i].x - rayon, p->bulles[i].y - rayon,
                    rayon * 2, rayon * 2,
                    p->joueur.x - 10, joueur_haut,
                    20, 60)) {
                p->joueur.vivant = 0; /* Le joueur meurt */
            }
        }
    }

    /* ===== COLLISIONS AVEC LES ÉCLAIRS ===== */
    for (j = 0; j < MAX_ECLAIRS; j++) {
        if (!p->eclairs[j].actif) continue;     /* On saute les inactifs */
        if (!p->joueur.vivant) break;            /* Inutile si déjà mort */
        if (p->eclairs[j].x > p->joueur.x - 30 && /* Aligné horizontalement */
            p->eclairs[j].x < p->joueur.x + 30 &&
            p->eclairs[j].y > SCREEN_H - 150) {    /* Au niveau du joueur */
            p->joueur.vivant = 0;                   /* Le joueur est foudroyé */
        }
    }

    /* ===== COLLISIONS AVEC LE BOSS ===== */

    /* Collision tir / boss */
    if (p->boss.actif && p->proj.actif) {
        if (collisionCercles(
                p->proj.x, p->proj.y, 5,      /* Le projectile */
                p->boss.x, p->boss.y, 40)) {   /* Le boss */
            p->proj.actif = 0;                  /* Le tir disparaît */
            p->boss.vie--;                       /* Le boss perd une vie */
            p->score += 500;                     /* On gagne des points */
            p->boss.etat = BOSS_HURT;           /* Animation de dégâts */
            p->boss.timer_hurt = 30;            /* Durée de l'état hurt */
            p->boss.vx = p->boss.vx * 1.3;    /* Le boss va plus vite */
            if (p->boss.vie <= 0) {
                p->boss.etat = BOSS_DIE;        /* Animation de mort */
                p->boss.actif = 0;              /* Le boss est vaincu */
            }
        }
    }

    /* Collision boss / joueur */
    if (p->boss.actif && p->joueur.vivant) {
        if (collisionCercles(
                p->boss.x, p->boss.y, 40,          /* Le boss */
                p->joueur.x, SCREEN_H - 65, 15)) { /* Le joueur */
            p->joueur.vivant = 0;                   /* Le joueur meurt */
        }
    }
}
