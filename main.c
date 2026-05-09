/*
 * main.c
 * Point d'entrée du programme.
 * - Initialise Allegro et la fenêtre
 * - Affiche le menu principal
 * - Lance la partie selon le choix utilisateur
 * - Libère les ressources à la fin
 */

 #include <allegro.h>  /* Librairie graphique principale */
#include "jeu.h"      /* Pour initialiserPartie() et boucleJeu() */
#include "affichage.h" /* Pour afficherMenu() et afficherRegles() */
#include "input.h"    /* Pour saisirPseudo() */
#include "sauvegarde.h" /* Pour chargerSauvegarde() */

int main() {
    BITMAP *buffer;   /* Buffer pour le double buffering (évite le scintillement) */
    int option = 0;   /* Option sélectionnée dans le menu : 0=Nouvelle partie */
    int quitter = 0;  /* 1 = on quitte le programme */
    char pseudo[MAX_PSEUDO] = ""; /* Pseudo saisi par le joueur */

    /* Initialisation d'Allegro */
    allegro_init();                                    /* On initialise la librairie */
    install_keyboard();                                /* On active la gestion du clavier */
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0); /* On ouvre une fenêtre 800x600 */
    set_window_title("Super Bulles");                  /* On définit le titre de la fenêtre */

    /* Création du buffer pour le double buffering */
    buffer = create_bitmap(SCREEN_W, SCREEN_H); /* On crée un bitmap de la taille de l'écran */

    /* Boucle du menu principal */
    while (!quitter) {
        afficherMenu(buffer, option); /* On affiche le menu avec l'option sélectionnée */

        /* Navigation dans le menu */
        if (key[KEY_UP]) {                         /* Flèche haut */
            option = (option - 1 + 4) % 4;        /* On remonte dans le menu (4 options) */
            rest(150);                              /* Petite pause pour éviter les répétitions */
        }
        if (key[KEY_DOWN]) {                       /* Flèche bas */
            option = (option + 1) % 4;             /* On descend dans le menu */
            rest(150);                              /* Petite pause pour éviter les répétitions */
        }

        if (key[KEY_ENTER]) { /* Si le joueur appuie sur Entrée */
            if (option == 0) { /* Nouvelle partie */
                saisirPseudo(pseudo);              /* On demande le pseudo */
                Partie p = initialiserPartie(pseudo); /* On crée la partie */
                boucleJeu(&p, buffer);             /* On lance le jeu */

            } else if (option == 1) { /* Reprendre */
                saisirPseudo(pseudo);              /* On demande le pseudo */
                int niv = chargerSauvegarde(pseudo); /* On charge la sauvegarde */
                if (niv == -1) {                   /* Si aucune sauvegarde trouvée */
                    /* On affiche un message d'erreur */
                    clear_to_color(buffer, makecol(0,0,0));
                    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2,
                        makecol(255,0,0), -1, "Aucune sauvegarde trouvee !");
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    rest(2000); /* On affiche le message 2 secondes */
                } else {
                    Partie p = initialiserPartie(pseudo); /* On crée la partie */
                    p.niveau = niv;                        /* On repart du niveau sauvegardé */
                    boucleJeu(&p, buffer);                 /* On lance le jeu */
                }

            } else if (option == 2) { /* Règles du jeu */
                afficherRegles(buffer);  /* On affiche les règles */
                while (!key[KEY_ESCAPE]) rest(16); /* On attend que le joueur appuie sur Échap */

            } else if (option == 3) { /* Quitter */
                quitter = 1; /* On sort de la boucle du menu */
            }
        }
    }

    /* Libération des ressources */
    destroy_bitmap(buffer); /* On libère le buffer */
    allegro_exit();         /* On ferme proprement Allegro */
    return 0;               /* Fin du programme */
}
END_OF_MAIN() /* Macro Allegro obligatoire sur Windows */