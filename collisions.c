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

int collisionCercles(float x1, float y1, float r1, float x2, float y2, float r2) {
    /* Calcule la distance entre les deux centres */
    float dx = x2 - x1;                        /* Différence en x entre les deux centres */
    float dy = y2 - y1;                        /* Différence en y entre les deux centres */
    float distance = sqrt(dx*dx + dy*dy);      /* Distance réelle entre les deux centres */
    return distance < (r1 + r2);              /* Collision si distance < somme des rayons */
}

int collisionRectangles(float x1, float y1, float w1, float h1,
                         float x2, float y2, float w2, float h2) {
    /* Vérifie si les deux rectangles se chevauchent sur les deux axes */
    if (x1 + w1 < x2) return 0; /* Le rectangle 1 est complètement à gauche du 2 */
    if (x2 + w2 < x1) return 0; /* Le rectangle 2 est complètement à gauche du 1 */
    if (y1 + h1 < y2) return 0; /* Le rectangle 1 est complètement au-dessus du 2 */
    if (y2 + h2 < y1) return 0; /* Le rectangle 2 est complètement au-dessus du 1 */
    return 1;                    /* Sinon il y a collision */
}

void gererCollisions(Partie *p) { /* Reçoit tout l'état de la partie */
    int i;                         /* Variable de boucle */
    int rayon;                     /* Rayon d'une bulle selon sa taille */

    for (i = 0; i < p->nb_bulles; i++) {  /* On parcourt toutes les bulles */
        if (!p->bulles[i].actif) continue; /* On saute les bulles inactives */

        rayon = p->bulles[i].taille * 15;  /* Rayon proportionnel à la taille */

        /* Collision tir / bulle (deux cercles) */
        if (p->proj.actif) { /* On vérifie seulement si un tir est en cours */
            if (collisionCercles(p->proj.x, p->proj.y, 5,          /* Cercle du projectile (rayon 5) */
                                 p->bulles[i].x, p->bulles[i].y, rayon)) { /* Cercle de la bulle */
                p->proj.actif = 0;                    /* Le projectile disparaît */
                diviserBulle(p->bulles, &p->nb_bulles, i); /* La bulle se divise */
                p->score += 100 * p->bulles[i].taille; /* On ajoute des points selon la taille */
            }
        }

        /* Collision bulle / joueur (cercle / rectangle) */
        if (p->joueur.vivant) { /* On vérifie seulement si le joueur est en vie */
            if (collisionRectangles(
                    p->bulles[i].x - rayon, p->bulles[i].y - rayon, /* Bounding box de la bulle */
                    rayon * 2, rayon * 2,
                    p->joueur.x - 10, p->joueur.y - 10,             /* Hitbox du joueur */
                    20, 20)) {
                p->joueur.vivant = 0; /* Le joueur meurt si une bulle le touche */
            }
        }
    }
}