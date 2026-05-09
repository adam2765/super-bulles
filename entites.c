/*
 * entites.c
 * Gestion des entités du jeu (joueur, bulles, projectiles).
 * - Initialiser et déplacer le joueur
 * - Ajouter, mettre à jour et diviser les bulles
 * - Gérer les tirs (créer et déplacer les projectiles)
 * - Gérer la sauvegarde et le chargement des parties
 */

 
#include "entites.h" /* On importe les structs et prototypes */
#include <allegro.h> /* Pour SCREEN_H */

/* ===================== JOUEUR ===================== */

Joueur initialiserJoueur(float x, float y) { /* Retourne un Joueur initialisé */
    Joueur j;      /* On crée un joueur local */
    j.x = x;      /* Position horizontale de départ */
    j.y = y;      /* Position verticale de départ */
    j.vivant = 1; /* Le joueur commence en vie */
    return j;     /* On retourne le joueur créé */
}

void deplacerJoueur(Joueur *j, int dir, float dt) { /* dt = temps écoulé en secondes */
    j->x += dir * VITESSE_JOUEUR * dt;               /* Déplacement fluide proportionnel au temps */
    if (j->x < 0) j->x = 0;                          /* Empêche de sortir par la gauche */
    if (j->x > LARGEUR_ECRAN) j->x = LARGEUR_ECRAN;  /* Empêche de sortir par la droite */
}

/* ===================== BULLES ===================== */

void ajouterBulle(Bulle *tab, int *nb, float x, float y, int taille) {
    if (*nb >= MAX_BULLES) return;   /* Sécurité : on ne dépasse pas le maximum */
    tab[*nb].x = x;                  /* Position horizontale */
    tab[*nb].y = y;                  /* Position verticale */
    tab[*nb].taille = taille;        /* Taille de la bulle */
    tab[*nb].vx = 0.3 * taille;     /* Vitesse horizontale très réduite */
    tab[*nb].vy = -0.4 * taille;    /* Vitesse verticale très réduite vers le haut */
    tab[*nb].actif = 1;              /* La bulle est active */
    (*nb)++;                          /* On incrémente le nombre total de bulles */
}

void mettreAJourBulles(Bulle *tab, int nb, float dt) {
    int i;           /* Variable de boucle */
    int rayon_bulle; /* Rayon de la bulle en pixels */
    int sol;         /* Position y du sol */

    sol = HAUTEUR_ECRAN - 35; /* Le sol est à 35 pixels du bas de l'écran */

    for (i = 0; i < nb; i++) {                         /* On parcourt toutes les bulles */
        if (!tab[i].actif) continue;                   /* On saute les bulles inactives */

        tab[i].x += tab[i].vx * dt * 60;              /* Déplacement horizontal fluide */
        tab[i].y += tab[i].vy * dt * 60;              /* Déplacement vertical fluide */

        /* Rebond sur le bord gauche ou droit */
        if (tab[i].x <= 0 || tab[i].x >= LARGEUR_ECRAN)
            tab[i].vx = tab[i].vx * -1;               /* On inverse la vitesse horizontale */

        /* Rebond sur le plafond */
        if (tab[i].y <= 0)
            tab[i].vy = tab[i].vy * -1;               /* On inverse la vitesse verticale */

        /* Gravité très douce */
        tab[i].vy += 0.3 * dt * 60;                   /* La bulle accélère très doucement */

        /* Rebond sur le sol */
        rayon_bulle = tab[i].taille * 20;              /* On calcule le rayon selon la taille */
        if (tab[i].y + rayon_bulle >= sol) {           /* Si le bas de la bulle touche le sol */
            tab[i].y = sol - rayon_bulle;              /* On repositionne au-dessus du sol */
            tab[i].vy = tab[i].vy * -1;               /* On inverse la vitesse : rebond ! */
        }
    }
}

void diviserBulle(Bulle *tab, int *nb, int idx) {
    float vx_origine; /* On mémorise la vitesse originale */

    if (tab[idx].taille <= 2) { /* Si c'est la plus petite taille */
        tab[idx].actif = 0;     /* Elle disparaît simplement */
        return;                  /* On arrête la fonction */
    }

    vx_origine = tab[idx].vx; /* On mémorise la vitesse originale */
    tab[idx].actif = 0;       /* La bulle touchée disparaît */

    /* Première bulle fille : part dans la direction d'origine */
    if (*nb < MAX_BULLES) {
        tab[*nb].x = tab[idx].x;               /* Même position x */
        tab[*nb].y = tab[idx].y;               /* Même position y */
        tab[*nb].taille = tab[idx].taille - 1; /* Une taille en moins */
        if (vx_origine > 0)
            tab[*nb].vx = 0.8;   /* Part doucement vers la droite */
        else
            tab[*nb].vx = -0.8;  /* Part doucement vers la gauche */
        tab[*nb].vy = -0.7;      /* Repart doucement vers le haut */
        tab[*nb].actif = 1;      /* La bulle est active */
        (*nb)++;                   /* On incrémente le nombre total */
    }

    /* Deuxième bulle fille : part dans la direction opposée */
    if (*nb < MAX_BULLES) {
        tab[*nb].x = tab[idx].x;               /* Même position x */
        tab[*nb].y = tab[idx].y;               /* Même position y */
        tab[*nb].taille = tab[idx].taille - 1; /* Une taille en moins */
        if (vx_origine > 0)
            tab[*nb].vx = -0.8;  /* Part doucement vers la gauche */
        else
            tab[*nb].vx = 0.8;   /* Part doucement vers la droite */
        tab[*nb].vy = -0.7;      /* Repart doucement vers le haut */
        tab[*nb].actif = 1;      /* La bulle est active */
        (*nb)++;                   /* On incrémente le nombre total */
    }
}

/* =================== PROJECTILE =================== */

void tirer(Joueur *j, Projectile *proj) {
    if (proj->actif) return;    /* Si un tir est déjà en cours, on ne peut pas retirer */
    proj->x = j->x;             /* Le tir part de la position x du joueur */
    proj->y = j->y;             /* Le tir part de la position y du joueur */
    proj->actif = 1;             /* Le projectile devient actif */
}

void mettreAJourProjectile(Projectile *proj, float dt) {
    if (!proj->actif) return;                /* Si pas de tir en cours, rien à faire */
    proj->y -= VITESSE_PROJECTILE * dt;      /* Le projectile monte selon le temps */
    if (proj->y < 0) proj->actif = 0;       /* S'il sort par le haut il disparaît */
}

/* =================== ECLAIRS =================== */

void lancerEclair(Eclair eclairs[], float x, float y) {
    int i; /* Variable de boucle */
    for (i = 0; i < MAX_ECLAIRS; i++) {  /* On cherche un slot libre */
        if (!eclairs[i].actif) {          /* Si ce slot est libre */
            eclairs[i].x = x;            /* Position x de la bulle */
            eclairs[i].y = y;            /* Position y de la bulle */
            eclairs[i].actif = 1;        /* L'éclair est actif */
            eclairs[i].frame = 0;        /* On repart de la première frame */
            return;                       /* On sort */
        }
    }
}

void mettreAJourEclairs(Eclair eclairs[], float dt) {
    int i; /* Variable de boucle */
    for (i = 0; i < MAX_ECLAIRS; i++) {
        if (!eclairs[i].actif) continue;     /* On saute les inactifs */
        eclairs[i].y += 250.0 * dt;          /* L'éclair tombe vers le bas */
        eclairs[i].frame++;                   /* On avance l'animation */
        if (eclairs[i].y > SCREEN_H - 35)   /* Si l'éclair touche le sol */
            eclairs[i].actif = 0;            /* Il disparaît */
    }
}
/* =================== BOSS =================== */

void initialiserBoss(Boss *boss) {
    boss->x = LARGEUR_ECRAN / 2; /* Le boss apparaît au centre de l'écran */
    boss->y = 100;                /* En haut de l'écran */
    boss->vx = 1.5;               /* Vitesse de départ */
    boss->vie = VIE_BOSS;        /* Nombre de vies */
    boss->actif = 1;              /* Le boss est actif */
    boss->frame = 0;              /* Compteur d'animation à zéro */
    boss->etat = BOSS_IDLE;      /* Le boss commence immobile */
    boss->timer_hurt = 0;        /* Pas de timer hurt au départ */
}

void mettreAJourBoss(Boss *boss, float dt) {
    if (!boss->actif) return;          /* Si le boss est mort, rien à faire */

    boss->frame++;                      /* On avance le compteur d'animation */

    /* Si le boss est touché, on attend avant de continuer */
    if (boss->etat == BOSS_HURT) {
        boss->timer_hurt--;             /* On décrémente le timer */
        if (boss->timer_hurt <= 0)     /* Si le timer est écoulé */
            boss->etat = BOSS_IDLE;    /* On repasse en idle */
        return;                         /* On ne déplace pas le boss pendant hurt */
    }

    /* Si le boss est en train de mourir, on ne fait rien */
    if (boss->etat == BOSS_DIE) return;

    /* Le boss se déplace horizontalement */
    boss->x += boss->vx * dt * 60;    /* Déplacement fluide */

    /* Rebond sur le bord gauche */
    if (boss->x <= 50) {
        boss->x = 50;                   /* On repositionne */
        boss->vx = boss->vx * -1;      /* On inverse la direction */
        boss->etat = BOSS_ATTACK;      /* On déclenche l'animation d'attaque */
    }

    /* Rebond sur le bord droit */
    if (boss->x >= LARGEUR_ECRAN - 50) {
        boss->x = LARGEUR_ECRAN - 50;  /* On repositionne */
        boss->vx = boss->vx * -1;      /* On inverse la direction */
        boss->etat = BOSS_ATTACK;      /* On déclenche l'animation d'attaque */
    }
}