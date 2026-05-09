/*
 * entites.c
 * Gestion des entités du jeu (joueur, bulles, projectiles).
 * - Initialiser et déplacer le joueur
 * - Ajouter, mettre à jour et diviser les bulles
 * - Gérer les tirs (créer et déplacer les projectiles)
 * - Gérer la sauvegarde et le chargement des parties
 */

 
#include "entites.h" /* On importe les structs et prototypes */

/* ===================== JOUEUR ===================== */

Joueur initialiserJoueur(float x, float y) { /* Retourne un Joueur initialisé */
    Joueur j;      /* On crée un joueur local */
    j.x = x;      /* Position horizontale de départ */
    j.y = y;      /* Position verticale de départ */
    j.vivant = 1; /* Le joueur commence en vie */
    return j;     /* On retourne le joueur créé */
}

void deplacerJoueur(Joueur *j, int dir, float dt) { /* dt = temps écoulé en secondes */
    j->x += dir * VITESSE_JOUEUR * dt;              /* Déplacement fluide proportionnel au temps */
    if (j->x < 0) j->x = 0;                         /* Empêche de sortir par la gauche */
    if (j->x > LARGEUR_ECRAN) j->x = LARGEUR_ECRAN; /* Empêche de sortir par la droite */
}

/* ===================== BULLES ===================== */

void ajouterBulle(Bulle *tab, int *nb, float x, float y, int taille) { /* Ajoute une bulle à la fin du tableau */
    if (*nb >= MAX_BULLES) return;   /* Sécurité : on ne dépasse pas le maximum */
    tab[*nb].x = x;                  /* Position horizontale */
    tab[*nb].y = y;                  /* Position verticale */
    tab[*nb].taille = taille;        /* Taille de la bulle */
    tab[*nb].vx = 2.0 * taille;     /* Vitesse horizontale proportionnelle à la taille */
    tab[*nb].vy = -3.0 * taille;    /* Vitesse verticale vers le haut */
    tab[*nb].actif = 1;              /* La bulle est active */
    (*nb)++;                          /* On incrémente le nombre total de bulles */
}

void mettreAJourBulles(Bulle *tab, int nb, float dt) { /* dt = temps écoulé en secondes */
    int i;                                              /* Variable de boucle */
    for (i = 0; i < nb; i++) {                         /* On parcourt toutes les bulles */
        if (!tab[i].actif) continue;                   /* On saute les bulles inactives */
        tab[i].x += tab[i].vx * dt * 60;              /* Déplacement horizontal fluide */
        tab[i].y += tab[i].vy * dt * 60;              /* Déplacement vertical fluide */
        if (tab[i].x <= 0 || tab[i].x >= LARGEUR_ECRAN) /* Si la bulle touche un bord gauche ou droit */
            tab[i].vx *= -1;                             /* Rebond : on inverse la vitesse horizontale */
        if (tab[i].y <= 0)    /* Si la bulle touche le plafond */
            tab[i].vy *= -1;  /* Rebond : on inverse la vitesse verticale */
        tab[i].vy += 3.0 * dt * 60; /* Gravité : la bulle accélère vers le bas */
    }
}

void diviserBulle(Bulle *tab, int *nb, int idx) { /* idx = indice de la bulle touchée */
    if (tab[idx].taille <= 1) { /* Si c'est la plus petite taille */
        tab[idx].actif = 0;     /* Elle disparaît simplement */
        return;                  /* On arrête la fonction */
    }
    float vx_origine = tab[idx].vx; /* On mémorise la vitesse originale */
    tab[idx].actif = 0;             /* La bulle touchée disparaît */

    if (*nb < MAX_BULLES) {                               /* Première bulle fille */
        tab[*nb].x = tab[idx].x;                         /* Même position x */
        tab[*nb].y = tab[idx].y;                         /* Même position y */
        tab[*nb].taille = tab[idx].taille - 1;           /* Une taille en moins */
        tab[*nb].vx = (vx_origine > 0 ? 1 : -1) * 3.0; /* Part dans la direction d'origine */
        tab[*nb].vy = -5.0;                               /* Repart vers le haut plus vite */
        tab[*nb].actif = 1;                               /* La bulle est active */
        (*nb)++;                                           /* On incrémente le nombre total */
    }

    if (*nb < MAX_BULLES) {                                /* Deuxième bulle fille */
        tab[*nb].x = tab[idx].x;                          /* Même position x */
        tab[*nb].y = tab[idx].y;                          /* Même position y */
        tab[*nb].taille = tab[idx].taille - 1;            /* Une taille en moins */
        tab[*nb].vx = (vx_origine > 0 ? -1 : 1) * 3.0;  /* Part dans la direction opposée */
        tab[*nb].vy = -5.0;                                /* Repart vers le haut plus vite */
        tab[*nb].actif = 1;                                /* La bulle est active */
        (*nb)++;                                            /* On incrémente le nombre total */
    }
}

/* =================== PROJECTILE =================== */

void tirer(Joueur *j, Projectile *proj) { /* Reçoit le joueur et le projectile */
    if (proj->actif) return;              /* Si un tir est déjà en cours, on ne peut pas retirer */
    proj->x = j->x;                       /* Le tir part de la position du joueur */
    proj->y = j->y;                       /* Le tir part de la position du joueur */
    proj->actif = 1;                       /* Le projectile devient actif */
}

void mettreAJourProjectile(Projectile *proj, float dt) { /* dt = temps écoulé en secondes */
    if (!proj->actif) return;                             /* Si pas de tir, rien à faire */
    proj->y -= VITESSE_PROJECTILE * dt;                   /* Le projectile monte selon le temps */
    if (proj->y < 0) proj->actif = 0;                    /* S'il sort par le haut il disparaît */
}