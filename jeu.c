/*
 * jeu.c
 * Logique globale du jeu.
 * - Initialiser une nouvelle partie (score, niveau, joueur)
 * - Lancer un niveau et retourner victoire ou défaite
 * - Contient la boucle principale du jeu (boucleJeu)
 * - Gère l'enchainement des niveaux et les écrans fin de niveau
 */
#include "jeu.h"     /* On importe toutes les fonctions dont on a besoin */
#include <allegro.h> /* Pour rest() qui fait des pauses en millisecondes */
#include <string.h>  /* Pour strncpy() qui copie du texte */

/* ===================================================
   INITIALISER UNE NOUVELLE PARTIE
   Cette fonction prépare tout avant de commencer
   =================================================== */
Partie initialiserPartie(char *pseudo) {
    Partie p;  /* On crée une partie vide */
    int i;     /* Variable pour parcourir les tableaux */
    int j;     /* Variable pour parcourir les éclairs */

    for (j = 0; j < MAX_ECLAIRS; j++)
        p.eclairs[j].actif = 0;            /* Tous les éclairs inactifs au départ */

    strncpy(p.pseudo, pseudo, MAX_PSEUDO); /* On mémorise le pseudo du joueur */
    p.niveau = 1;                          /* On commence au niveau 1 */
    p.score = 0;                           /* Le score part de zéro */
    p.temps = TEMPS_NIVEAU;               /* On donne tout le temps au joueur */
    p.nb_bulles = 0;                      /* Pas de bulles au départ */
    p.frame = 0;                          /* Compteur d'animation à zéro */
    p.etat_joueur = ETAT_IDLE;           /* Le joueur commence immobile */
    p.arme_active = 0;                    /* On commence avec l'arme de base */
    p.arme_timer = 0;                     /* Pas d'arme temporaire au départ */
    p.boss.actif = 0;                     /* Pas de boss au départ */
    p.boss.etat = BOSS_IDLE;             /* Le boss commence en état idle */

    p.joueur = initialiserJoueur(SCREEN_W/2, SCREEN_H - 35); /* Joueur sur le sol */
    p.proj.actif = 0;                     /* Pas de tir au départ */

    for (i = 0; i < MAX_BULLES; i++)
        p.bulles[i].actif = 0;            /* Chaque bulle est marquée comme inexistante */

    return p; /* On retourne la partie prête */
}

/* ===================================================
   PLACER LES BULLES SELON LE NIVEAU
   Plus le niveau est élevé, plus c'est difficile
   =================================================== */
static void placerBulles(Partie *p) {
    int i;                    /* Variable de boucle */
    for (i = 0; i < MAX_BULLES; i++)
        p->bulles[i].actif = 0; /* On efface toutes les bulles */
    p->nb_bulles = 0;           /* On remet le compteur à zéro */

    if (p->niveau == 1) {
        /* Niveau 1 : une seule grande bulle pour s'entraîner */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/2, 150, 3);
    }
    else if (p->niveau == 2) {
        /* Niveau 2 : deux grandes bulles, plus difficile */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/3, 150, 3);
        ajouterBulle(p->bulles, &p->nb_bulles, 2*SCREEN_W/3, 150, 3);
    }
    else if (p->niveau == 3) {
        /* Niveau 3 : trois bulles de tailles différentes */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/4, 150, 3);   /* Grande bulle à gauche */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/2, 100, 2);   /* Bulle moyenne au centre */
        ajouterBulle(p->bulles, &p->nb_bulles, 3*SCREEN_W/4, 150, 3); /* Grande bulle à droite */
    }
    else if (p->niveau == 4) {
        /* Niveau 4 : quatre bulles, le plus difficile */
        ajouterBulle(p->bulles, &p->nb_bulles, SCREEN_W/5, 150, 3);   /* Grande bulle */
        ajouterBulle(p->bulles, &p->nb_bulles, 2*SCREEN_W/5, 100, 2); /* Bulle moyenne */
        ajouterBulle(p->bulles, &p->nb_bulles, 3*SCREEN_W/5, 100, 2); /* Bulle moyenne */
        ajouterBulle(p->bulles, &p->nb_bulles, 4*SCREEN_W/5, 150, 3); /* Grande bulle */
    }
}

/* ===================================================
   COMPTER LES BULLES ENCORE ACTIVES
   On utilise ça pour savoir si le niveau est gagné
   =================================================== */
static int compterBullesActives(Partie *p) {
    int i;           /* Variable de boucle */
    int nb = 0;      /* Compteur de bulles actives */

    for (i = 0; i < p->nb_bulles; i++)  /* On parcourt toutes les bulles */
        if (p->bulles[i].actif) nb++;    /* On ajoute 1 pour chaque bulle encore en vie */

    return nb; /* On retourne le nombre de bulles actives */
}

/* ===================================================
   METTRE À JOUR L'ANIMATION DU JOUEUR
   On choisit quelle animation afficher selon l'action
   =================================================== */
static void mettreAJourAnimation(Partie *p) {
    p->frame++; /* On avance le compteur d'animation d'un pas */

    /* Si le joueur est mort, on bloque l'animation sur "mort" et on ne change plus */
    if (!p->joueur.vivant) {
        p->etat_joueur = ETAT_DEAD; /* On force l'état mort */
        return;                      /* On sort sans changer l'état */
    }

    /* Sinon on choisit l'animation selon ce que fait le joueur */
    if (p->proj.actif)                        /* Si un tir est en cours */
        p->etat_joueur = ETAT_SHOOT;          /* Animation de tir */
    else if (key[KEY_LEFT] || key[KEY_RIGHT]) /* Si le joueur se déplace */
        p->etat_joueur = ETAT_RUN;            /* Animation de course */
    else                                       /* Sinon le joueur est immobile */
        p->etat_joueur = ETAT_IDLE;           /* Animation immobile */
}

/* ===================================================
   LANCER UN NIVEAU
   Cette fonction fait tourner un niveau entier
   Elle retourne 1 si gagné, 0 si perdu
   =================================================== */
int lancerNiveau(Partie *p, int numero, BITMAP *buffer) {
    int i;            /* Variable de boucle */
    int quitter = 0;  /* Devient 1 quand on doit sortir de la boucle */
    float dt = 0.013; /* Temps entre deux images (~60 images par seconde) */
    int j;            /* Variable de boucle pour les éclairs */

    /* On prépare le niveau */
    p->niveau = numero;                                             /* On note le numéro du niveau */
    p->joueur = initialiserJoueur(SCREEN_W/2, SCREEN_H - 35);     /* Joueur sur le sol */
    p->joueur.vivant = 1;                                          /* Le joueur est en vie */
    p->proj.actif = 0;                                             /* Pas de tir au départ */
    p->temps = TEMPS_NIVEAU;                                       /* On remet le temps à plein */
    p->frame = 0;                                                  /* Compteur d'animation à zéro */
    p->etat_joueur = ETAT_IDLE;                                   /* Le joueur commence immobile */
    p->arme_active = 0;                                            /* On repart avec l'arme de base */
    p->arme_timer = 0;                                             /* Pas d'arme temporaire */
    p->boss.actif = 0;                                             /* Pas de boss par défaut */
    p->boss.etat = BOSS_IDLE;                                     /* État initial du boss */

    for (j = 0; j < MAX_ECLAIRS; j++)
        p->eclairs[j].actif = 0;  /* On efface tous les éclairs */

    placerBulles(p); /* On place les bulles pour ce niveau */

    /* Au niveau 4, on initialise le boss */
    if (p->niveau == 4)
        initialiserBoss(&p->boss); /* On crée le boss slime */

    /* Décompte 3... 2... 1... avant que le niveau commence */
    for (i = 3; i >= 1; i--) {
        afficherDecompte(buffer, i, p->niveau); /* On passe le niveau */
        rest(1000);                  /* On attend 1 seconde */
    }

    /* =============================================
       BOUCLE PRINCIPALE DU NIVEAU
       Cette boucle tourne ~60 fois par seconde
       ============================================= */
    while (!quitter) {

        /* 1. On lit les touches du clavier */
        lireEntrees(p, &quitter, dt);

        /* 2. On met à jour l'animation du joueur */
        mettreAJourAnimation(p);

        /* 3. On déplace les bulles */
        mettreAJourBulles(p->bulles, p->nb_bulles, dt);

        /* 4. Au niveau 3+, les bulles lancent des éclairs toutes les 2 secondes */
        if (p->niveau >= 3 && p->frame % 120 == 0 && p->nb_bulles > 0) {
            int idx = p->frame % p->nb_bulles;  /* On choisit une bulle au hasard */
            if (p->bulles[idx].actif)           /* Si la bulle est active */
                lancerEclair(p->eclairs, p->bulles[idx].x, p->bulles[idx].y); /* On lance l'éclair */
        }
        mettreAJourEclairs(p->eclairs, dt); /* On fait tomber les éclairs */

        /* 5. On met à jour le boss au niveau 4 */
        if (p->boss.actif)
            mettreAJourBoss(&p->boss, dt); /* On déplace le boss */

        if (p->boss.actif && p->frame % 180 == 0 && p->boss.etat != BOSS_HURT) {
            ajouterBulle(p->bulles, &p->nb_bulles,
                p->boss.x,        /* La bulle part de la position x du boss */
                p->boss.y + 30,   /* La bulle part du bas du boss */
                1);               /* Petite bulle */
            p->boss.etat = BOSS_ATTACK; /* Animation attaque quand il lance une bulle */
        }
        /* Si le boss est mort on attend la fin de son animation puis on le cache */
        if (p->boss.etat == BOSS_DIE) {
            p->boss.frame++;                          /* On avance l'animation de mort */
            if (p->boss.frame > 60) {                /* Après 60 frames d'animation */
                p->boss.etat = BOSS_IDLE;            /* On arrête d'afficher le boss */
                p->boss.actif = 0;                   /* On le désactive complètement */
            }
        }

        /* 7. On déplace le projectile */
        mettreAJourProjectile(&p->proj, dt);

        /* 8. On vérifie les collisions */
        gererCollisions(p);

        /* 9. On force l'animation de mort si le joueur vient de mourir */
        if (!p->joueur.vivant)
            p->etat_joueur = ETAT_DEAD; /* On force l'état mort */

        /* 10. On fait passer le temps seulement si le joueur est vivant */
        if (p->joueur.vivant)
            p->temps -= dt; /* On enlève le temps écoulé */

        /* 11. On dessine tout à l'écran */
        afficherEcranJeu(buffer, p);

        /* 12. On vérifie si le joueur est mort APRÈS l'affichage */
        if (!p->joueur.vivant) {
            int t = 0;
            while (t < 40) {                   /* On joue 40 frames d'animation de mort */
                p->frame++;                     /* On avance l'animation */
                p->etat_joueur = ETAT_DEAD;    /* On force l'état mort */
                afficherEcranJeu(buffer, p);   /* On affiche le joueur mort */
                rest(16);                       /* 60 fps */
                t++;                            /* On passe à la frame suivante */
            }
            rest(300); /* Petite pause avant de quitter */
            return 0;  /* Défaite */
        }

        /* 13. Si le temps est écoulé */
        if (p->temps <= 0)
            return 0; /* Défaite faute de temps */

        /* 14. Condition de victoire selon le niveau */
        if (p->niveau == 4) {
            /* Au niveau 4, il faut vaincre les bulles ET le boss */
            if (compterBullesActives(p) == 0 && !p->boss.actif)
                return 1; /* Victoire ! */
        } else {
            /* Aux niveaux 1-3, il suffit d'éliminer toutes les bulles */
            if (compterBullesActives(p) == 0)
                return 1; /* Victoire ! */
        }

        /* 15. On attend pour avoir 60 images par seconde */
        rest(16);
    }

    return 0; /* Si le joueur a appuyé sur Échap → défaite */
}

/* ===================================================
   BOUCLE PRINCIPALE DU JEU
   Cette fonction enchaîne les 4 niveaux
   =================================================== */
void boucleJeu(Partie *p, BITMAP *buffer) {
    int resultat; /* Stocke le résultat : 1=victoire, 0=défaite */

    while (p->niveau <= NB_NIVEAUX) {        /* On joue les niveaux un par un */
        resultat = lancerNiveau(p, p->niveau, buffer); /* On lance le niveau en cours */
        if (resultat == 1) {
            sauvegarderMeilleurScore(p->score);          /* On sauvegarde d'abord le record */
            afficherVictoire(buffer, p->score);          /* Puis on affiche avec le bon meilleur score */
            p->niveau++;                                  /* On passe au niveau suivant */
            sauvegarder(p->pseudo, p->niveau);           /* On sauvegarde la progression */
            clear_keybuf();                               /* On vide le buffer clavier */
            readkey();                                    /* On attend une touche */
        }

        else {
            /* Le joueur a perdu — on lui demande s'il veut recommencer */
            afficherDefaite(buffer);   /* On affiche l'écran de défaite */
            clear_keybuf();             /* On vide le buffer clavier */

            afficherDefaite(buffer);
            clear_keybuf();

            int choix = readkey() >> 8;
            if (choix != KEY_R)
                return;
            /* On lit le choix du joueur */
             choix = readkey() >> 8; /* On attend une touche */

            if (choix != KEY_R)         /* Si ce n'est pas R */
                return;                  /* On retourne au menu */
            /* Sinon on continue la boucle = on relance le même niveau */
        }
    }

    afficherVictoire(buffer, p->score); /* Victoire finale après tous les niveaux */
    sauvegarderMeilleurScore(p->score); /* On sauvegarde si c'est un record */
    clear_keybuf();                      /* On vide le buffer clavier */
    readkey();                           /* On attend une touche */
}