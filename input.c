/*
 * input.c
 * Gestion des entrées clavier (Allegro 4).
 * - Lire les touches pressées à chaque frame
 * - Transmettre les actions du joueur à la logique de jeu
 * - Gérer les déplacements (flèches gauche/droite)
 * - Gérer le tir (espace) et la navigation dans les menus
 */

#include "input.h"  /* On importe les prototypes */
#include <string.h> /* Pour strlen() */

void lireEntrees(Joueur *j, Projectile *proj, int *quitter, float dt) { /* dt = temps écoulé en secondes */
    if (key[KEY_ESCAPE])       /* Si le joueur appuie sur Échap */
        *quitter = 1;           /* On signale qu'il faut quitter */
    if (key[KEY_LEFT])         /* Si la flèche gauche est appuyée */
        deplacerJoueur(j, -1, dt); /* On déplace le joueur vers la gauche */
    if (key[KEY_RIGHT])        /* Si la flèche droite est appuyée */
        deplacerJoueur(j, 1, dt);  /* On déplace le joueur vers la droite */
    if (key[KEY_SPACE])        /* Si la barre espace est appuyée */
        tirer(j, proj);        /* On crée un projectile à la position du joueur */
}

void saisirPseudo(char *pseudo) { /* Reçoit un tableau de caractères à remplir */
    int i = 0;                     /* Index du caractère en cours de saisie */
    int touche;                    /* Stocke la touche pressée */

    clear_keybuf();                /* On vide le buffer clavier avant la saisie */

    while (1) {                    /* Boucle jusqu'à ce que le joueur appuie sur Entrée */
        touche = readkey();        /* On attend une touche et on la lit */
        touche = touche & 0xFF;    /* On garde seulement le caractère ASCII */

        if (touche == 13) break;   /* Si c'est Entrée (ASCII 13) on arrête la saisie */

        if (touche == 8 && i > 0) { /* Si c'est Backspace et qu'il y a des caractères */
            i--;                     /* On recule d'un caractère */
            pseudo[i] = '\0';        /* On efface le dernier caractère */
        }
        else if (i < MAX_PSEUDO - 1 && touche >= 32) { /* Si c'est un caractère valide */
            pseudo[i] = (char)touche; /* On ajoute le caractère au pseudo */
            i++;                       /* On avance d'un caractère */
            pseudo[i] = '\0';          /* On termine la chaîne */
        }
    }
}