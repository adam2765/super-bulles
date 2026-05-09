#include <allegro.h>    /* Librairie graphique principale */
#include <string.h>     /* Pour strncpy */
#include "jeu.h"        /* Pour initialiserPartie() et boucleJeu() */
#include "affichage.h"  /* Pour afficherMenu() et chargerSprites() */
#include "input.h"      /* Pour saisirPseudo() */
#include "sauvegarde.h" /* Pour chargerSauvegarde() */

int main() {
    BITMAP *buffer;               /* Buffer pour le double buffering */
    int option = 0;               /* Option sélectionnée dans le menu */
    int quitter = 0;              /* 1 = on quitte le programme */
    char pseudo[MAX_PSEUDO] = ""; /* Pseudo saisi par le joueur */

    /* Initialisation d'Allegro */
    allegro_init();                                          /* On initialise la librairie Allegro */
    install_keyboard();                                      /* On active la gestion du clavier */
    set_color_depth(32);                                     /* Profondeur de couleur 32 bits */
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);  /* Fenêtre 800x600 */
    set_window_title("Super Bulles");                        /* Titre de la fenêtre */

    buffer = create_bitmap(SCREEN_W, SCREEN_H); /* Buffer de la taille de l'écran */
    chargerSprites();                            /* On charge les sprites du joueur */
    chargerSpritesEclair();                      /* On charge les sprites de l'éclair */
    chargerSpritesBoss();                        /* On charge les sprites du boss */
    chargerFonds();         /* On charge les fonds de niveau */

    /* Écran d'intro avec l'histoire */
    afficherIntro(buffer);                       /* On affiche l'écran d'intro */
    while (!key[KEY_ENTER]) rest(16);            /* On attend que le joueur appuie sur Entrée */

    /* Boucle du menu principal */
    while (!quitter) {
        afficherMenu(buffer, option);            /* On affiche le menu */
        clear_keybuf();                          /* On vide le buffer clavier avant de lire */

        int touche = readkey() >> 8;             /* On attend un seul appui de touche */
        if (touche == KEY_UP)                    /* Flèche haut */
            option = (option - 1 + 4) % 4;      /* On remonte dans le menu */
        if (touche == KEY_DOWN)                  /* Flèche bas */
            option = (option + 1) % 4;          /* On descend dans le menu */
        if (touche == KEY_ENTER) {              /* Entrée : on valide */
            rest(200);                           /* Petite pause pour éviter les double-appuis */

            if (option == 0) {                  /* Nouvelle partie */
                saisirPseudo(pseudo, buffer);    /* On demande le pseudo avec affichage */
                Partie p = initialiserPartie(pseudo); /* On crée la partie */
                boucleJeu(&p, buffer);           /* On lance le jeu */

            } else if (option == 1) {           /* Reprendre */
                saisirPseudo(pseudo, buffer);    /* On demande le pseudo avec affichage */
                int niv = chargerSauvegarde(pseudo); /* On charge la sauvegarde */
                if (niv == -1) {                /* Si aucune sauvegarde trouvée */
                    clear_to_color(buffer, makecol(0,0,0)); /* Écran noir */
                    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2,
                        makecol(255,0,0), -1, "Aucune sauvegarde trouvee !"); /* Message erreur */
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);    /* Affichage */
                    rest(2000);                 /* On affiche 2 secondes */
                } else {
                    Partie p = initialiserPartie(pseudo); /* On crée la partie */
                    p.niveau = niv;             /* On repart du niveau sauvegardé */
                    boucleJeu(&p, buffer);       /* On lance le jeu */
                }

            } else if (option == 2) {           /* Règles du jeu */
                afficherRegles(buffer);          /* On affiche les règles */
                while (!key[KEY_ESC]) rest(16); /* On attend que le joueur appuie sur Échap */

            } else if (option == 3) {           /* Quitter */
                quitter = 1;                     /* On sort de la boucle du menu */
            }
        }
    }

    /* Libération des ressources */
    libererSprites();       /* On libère les sprites du joueur */
    libererSpritesEclair(); /* On libère les sprites de l'éclair */
    libererSpritesBoss();   /* On libère les sprites du boss */
    libererFonds();         /* On libère les fonds de niveau */

    destroy_bitmap(buffer); /* On libère le buffer */
    allegro_exit();         /* On ferme Allegro proprement */
    return 0;               /* Fin du programme */
}
END_OF_MAIN() /* Macro Allegro obligatoire sur Windows */