/*
 * jeu.c
 * Logique globale du jeu.
 * - Initialiser une nouvelle partie (score, niveau, joueur)
 * - Lancer un niveau et retourner victoire ou défaite
 * - Contient la boucle principale du jeu (boucleJeu)
 * - Gère l'enchainement des niveaux et les écrans fin de niveau
 */
#include "jeu.h"    /* On importe les prototypes */
#include<stdlib.h>
#include <allegro.h> /* Pour rest() et les timers Allegro */

Partie initialiserPartie(char *pseudo) { /* Reçoit le pseudo saisi par le joueur */
    Partie p;                             /* On crée une partie locale */
    int i;                                /* Variable de boucle */

    strncpy(p.pseudo, pseudo, MAX_PSEUDO); /* On copie le pseudo dans la partie */
    p.niveau = 1;                          /* On commence au niveau 1 */
    p.score = 0;                           /* Score initial à 0 */
    p.temps = TEMPS_NIVEAU;               /* Temps plein au démarrage */
    p.nb_bulles = 0;                      /* Pas encore de bulles */

    /* On initialise le joueur au centre en bas de l'écran */
    p.joueur = initialiserJoueur(SCREEN_W / 2, SCREEN_H - 50);

    /* On initialise le projectile comme inactif */
    p.proj.actif = 0; /* Pas de tir au démarrage */

    /* On vide le tableau de bulles */
    for (i = 0; i < MAX_BULLES; i++)
        p.bulles[i].actif = 0; /* Toutes les bulles sont inactives au départ */

    return p; /* On retourne la partie initialisée */
}

int lancerNiveau(Partie *p, BITMAP *buffer) { /* Lance le niveau en cours, retourne 1=victoire 0=défaite */
    int i;                                     /* Variable de boucle */
    int quitter = 0;                           /* Flag pour quitter la boucle */
    float dt = 0.016;                          /* Delta time fixe : environ 60 fps */

    /* On remet le joueur en vie et au centre */
    p->joueur = initialiserJoueur(SCREEN_W / 2, SCREEN_H - 50);
    p->joueur.vivant = 1;  /* Le joueur est en vie */
    p->proj.actif = 0;     /* Pas de tir au démarrage */
    p->temps = TEMPS_NIVEAU; /* On remet le temps à zéro */
    p->nb_bulles = 0;        /* On vide le tableau de bulles */

    /* On place les bulles selon le niveau */
    if (p->niveau == 1) { /* Niveau 1 : une grande bulle */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/2, 100, 3);
    } else if (p->niveau == 2) { /* Niveau 2 : deux grandes bulles */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/3, 100, 3);
        ajouterBulle(p->bulles, &p->nb_bulles, 2*SCREEN_W/3, 100, 3);
    } else if (p->niveau == 3) { /* Niveau 3 : trois bulles de tailles différentes */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/4, 100, 3);
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/2, 80, 2);
        ajouterBulle(p->bulles, &p->nb_bulles, 3*SCREEN_W/4, 100, 3);
    } else if (p->niveau == 4) { /* Niveau 4 : quatre bulles */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/5, 100, 3);
        ajouterBulle(p->bulles, &p->nb_bulles, 2*SCREEN_W/5, 80, 2);
        ajouterBulle(p->bulles, &p->nb_bulles, 3*SCREEN_W/5, 80, 2);
        ajouterBulle(p->bulles, &p->nb_bulles, 4*SCREEN_W/5, 100, 3);
    }

    /* Décompte 3-2-1 avant le début du niveau */
    for (i = 3; i >= 1; i--) {       /* On affiche 3, puis 2, puis 1 */
        afficherDecompte(buffer, i);   /* On affiche le chiffre */
        rest(1000);                    /* On attend 1 seconde */
    }

    /* Boucle principale du niveau */
    while (!quitter) {
        /* Lire les entrées clavier */
        lireEntrees(&p->joueur, &p->proj, &quitter, dt);

        /* Mettre à jour les entités */
        mettreAJourBulles(p->bulles, p->nb_bulles, dt); /* On déplace les bulles */
        mettreAJourProjectile(&p->proj, dt);              /* On déplace le projectile */

        /* Gérer les collisions */
        gererCollisions(p); /* On détecte toutes les collisions */

        /* Mettre à jour le temps restant */
        p->temps -= dt; /* On soustrait le temps écoulé */

        /* Vérifier les conditions de fin de niveau */
        if (!p->joueur.vivant) return 0; /* Le joueur est mort : défaite */
        if (p->temps <= 0) return 0;     /* Temps écoulé : défaite */

        /* Vérifier si toutes les bulles sont détruites */
        int bulles_restantes = 0;                     /* Compteur de bulles encore actives */
        for (i = 0; i < p->nb_bulles; i++)
            if (p->bulles[i].actif) bulles_restantes++; /* On compte les bulles actives */
        if (bulles_restantes == 0) return 1;          /* Plus de bulles : victoire ! */

        /* Afficher le jeu */
        afficherEcranJeu(buffer, p); /* On dessine tout à l'écran */

        rest(16); /* On attend ~16ms pour avoir environ 60 fps */
    }

    return 0; /* Si on quitte la boucle autrement : défaite par défaut */
}

void boucleJeu(Partie *p, BITMAP *buffer) { /* Gère l'enchaînement des niveaux */
    int resultat;                             /* 1=victoire, 0=défaite */

    while (p->niveau <= NB_NIVEAUX) {        /* On joue tant qu'il reste des niveaux */
        resultat = lancerNiveau(p, buffer);   /* On lance le niveau en cours */

        if (resultat == 1) {                  /* Si victoire du niveau */
            afficherVictoire(buffer, p->score); /* On affiche l'écran de victoire */
            sauvegarder(p->pseudo, p->niveau);  /* On sauvegarde la progression */
            readkey();                           /* On attend que le joueur appuie sur une touche */
            p->niveau++;                         /* On passe au niveau suivant */
        } else {                              /* Si défaite */
            afficherDefaite(buffer);          /* On affiche l'écran de défaite */
            readkey();                         /* On attend que le joueur appuie sur une touche */
            return;                            /* On retourne au menu principal */
        }
    }

    /* Le joueur a terminé tous les niveaux */
    afficherVictoire(buffer, p->score); /* Écran de victoire finale */
    readkey();                           /* On attend une touche */
}