/*
 * input.c
 * Gestion des entrées clavier (Allegro 4).
 * - Lire les touches pressées à chaque frame
 * - Transmettre les actions du joueur à la logique de jeu
 * - Gérer les déplacements (flèches gauche/droite)
 * - Gérer le tir (espace) et la navigation dans les menus
 */
#include "input.h"  /* On importe les prototypes définis dans input.h */

void lireEntrees(Joueur *j, Projectile *p, int *quitter) {  /* Reçoit le joueur, le projectile et le flag pour quitter */

    /* Quitter le jeu */
    if (key[KEY_ESCAPE])  /* Si le joueur appuie sur Échap... */
        *quitter = 1;      /* ...on signale qu'il faut quitter */

    /* Déplacements */
    if (key[KEY_LEFT])              /* Si la flèche gauche est appuyée... */
        deplacerJoueur(j, -1);      /* ...on déplace le joueur vers la gauche */

    if (key[KEY_RIGHT])             /* Si la flèche droite est appuyée... */
        deplacerJoueur(j, 1);       /* ...on déplace le joueur vers la droite */

    /* Tir */
    if (key[KEY_SPACE])             /* Si la barre espace est appuyée... */
        tirerProjectile(p, j);      /* ...on crée un projectile à la position du joueur */
}