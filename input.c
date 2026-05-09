/*
 * input.c
 * Gestion des entrées clavier (Allegro 4).
 * - Lire les touches pressées à chaque frame
 * - Transmettre les actions du joueur à la logique de jeu
 * - Gérer les déplacements (flèches gauche/droite)
 * - Gérer le tir (espace) et la navigation dans les menus
 */

#include "input.h"   /* On importe les prototypes */

#include <stdio.h>
#include <string.h>  /* Pour strlen() */

void lireEntrees(Partie *p, int *quitter, float dt) {
    /* Reçoit toute la partie, le flag pour quitter et le temps écoulé */

    /* Quitter le niveau avec Échap */
    if (key[KEY_ESC])   /* Si le joueur appuie sur Échap */
        *quitter = 1;    /* On signale qu'il faut quitter */

    /* Déplacement gauche */
    if (key[KEY_LEFT])                    /* Si la flèche gauche est appuyée */
        deplacerJoueur(&p->joueur, -1, dt); /* On déplace le joueur vers la gauche */

    /* Déplacement droite */
    if (key[KEY_RIGHT])                  /* Si la flèche droite est appuyée */
        deplacerJoueur(&p->joueur, 1, dt); /* On déplace le joueur vers la droite */

    /* Tir selon l'arme équipée */
    if (key[KEY_SPACE]) {                /* Si la barre espace est appuyée */
        if (p->arme_active == 1) {       /* Si le joueur a l'arme rapide */
            /* Arme temporaire : on remet le projectile actif à 0 pour pouvoir retirer */
            p->proj.actif = 0;           /* On efface le tir précédent */
            tirer(&p->joueur, &p->proj); /* On crée immédiatement un nouveau tir */
        } else {                          /* Sinon on utilise l'arme de base */
            tirer(&p->joueur, &p->proj); /* Un seul tir à la fois (tirer() vérifie si actif) */
        }
    }

    /* Mise à jour du timer de l'arme temporaire */
    if (p->arme_active == 1) {                /* Si une arme temporaire est équipée */
        p->arme_timer -= dt;                  /* On réduit le temps restant */
        if (p->arme_timer <= 0) {             /* Si le temps est écoulé */
            p->arme_active = 0;               /* On désactive l'arme temporaire */
            p->arme_timer = 0;                /* On remet le timer à zéro */
        }
    }
}

  /* Reçoit un tableau de caractères à remplir */
void saisirPseudo(char *pseudo, BITMAP *buffer) {
    int i = 0;       /* Index du caractère en cours */
    int touche;      /* Touche pressée */
    char affiche[MAX_PSEUDO + 1]; /* Texte affiché avec curseur */

    pseudo[0] = '\0'; /* On vide le pseudo */
    clear_keybuf();   /* On vide le buffer clavier */

    while (1) {
        /* On affiche l'écran de saisie */
        clear_to_color(buffer, makecol(0, 0, 0));  /* Fond noir */
        textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 - 40,
            makecol(255, 255, 0), -1, "Entrez votre pseudo :");
        sprintf(affiche, "%s_", pseudo);            /* On ajoute un curseur _ */
        textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2,
            makecol(255, 255, 255), -1, "%s", affiche); /* On affiche le pseudo */
        textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 + 40,
            makecol(150, 150, 150), -1, "Appuyez sur ENTREE pour valider");
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche */

        touche = readkey();         /* On attend une touche */
        touche = touche & 0xFF;     /* On garde le code ASCII */

        if (touche == 13) break;    /* Entrée = on valide */
        if (touche == 8 && i > 0) { /* Backspace */
            i--;
            pseudo[i] = '\0';
        }
        else if (i < MAX_PSEUDO - 1 && touche >= 32) { /* Caractère valide */
            pseudo[i] = (char)touche;
            i++;
            pseudo[i] = '\0';
        }
    }
}