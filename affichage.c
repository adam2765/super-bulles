#include "affichage.h"  /* On importe les prototypes d'affichage */
#include <stdio.h>      /* Pour sprintf() qui formate du texte */

/* ===== COULEURS ===== */
#define NOIR        makecol(0, 0, 0)       /* Noir */
#define BLANC       makecol(255, 255, 255) /* Blanc */
#define JAUNE       makecol(255, 220, 0)   /* Jaune doré */
#define ROUGE_CLAIR makecol(255, 100, 100) /* Rouge clair */
#define BLEU        makecol(30, 80, 200)   /* Bleu */
#define BLEU_CLAIR  makecol(100, 180, 255) /* Bleu clair */
#define GRIS        makecol(120, 120, 120) /* Gris */
#define GRIS_CLAIR  makecol(200, 200, 200) /* Gris clair */

/* ===== CONSTANTES ===== */
#define HUD_HAUTEUR  55  /* Hauteur de la barre d'info en haut en pixels */
#define SOL_HAUTEUR  35  /* Hauteur du sol en bas en pixels */
#define ECHELLE_SPRITE 3 /* On agrandit le sprite joueur x3 pour qu'il soit visible */
#define ECHELLE_BOSS   4 /* On agrandit le sprite boss x4 pour qu'il soit imposant */
#define NB_ETOILES   120 /* Nombre d'étoiles dans le fond */

/* ===== SPRITES DU JOUEUR ===== */
#define NB_IDLE  4  /* Nombre d'images pour l'animation immobile */
#define NB_RUN   6  /* Nombre d'images pour l'animation de course */
#define NB_SHOOT 3  /* Nombre d'images pour l'animation de tir */
#define NB_DEAD  4  /* Nombre d'images pour l'animation de mort */

static BITMAP *anim_idle[NB_IDLE];   /* Images de l'animation "immobile" */
static BITMAP *anim_run[NB_RUN];     /* Images de l'animation "course" */
static BITMAP *anim_shoot[NB_SHOOT]; /* Images de l'animation "tir" */
static BITMAP *anim_dead[NB_DEAD];   /* Images de l'animation "mort" */

/* ===== CHARGEMENT DES SPRITES JOUEUR ===== */
void chargerSprites() {
    int i;                 /* Variable pour parcourir les images */
    char nom_fichier[200]; /* Nom du fichier à charger */

    /* On charge les images de l'animation "immobile" */
    for (i = 0; i < NB_IDLE; i++) {
        sprintf(nom_fichier, "sprites/marine 1 rifle_idle_%d.bmp", i+1); /* On construit le nom */
        anim_idle[i] = load_bitmap(nom_fichier, NULL);                    /* On charge l'image */
    }

    /* On charge les images de l'animation "course" */
    for (i = 0; i < NB_RUN; i++) {
        sprintf(nom_fichier, "sprites/marine 1 rifle_run_%d.bmp", i); /* On construit le nom */
        anim_run[i] = load_bitmap(nom_fichier, NULL);                  /* On charge l'image */
    }

    /* On charge les images de l'animation "tir" */
    for (i = 0; i < NB_SHOOT; i++) {
        sprintf(nom_fichier, "sprites/marine 1 rifle_shoot_%d.bmp", i); /* On construit le nom */
        anim_shoot[i] = load_bitmap(nom_fichier, NULL);                  /* On charge l'image */
    }

    /* On charge les images de l'animation "mort" */
    for (i = 0; i < NB_DEAD; i++) {
        sprintf(nom_fichier, "sprites/marine 1 rifle_dead_%d.bmp", i); /* On construit le nom */
        anim_dead[i] = load_bitmap(nom_fichier, NULL);                  /* On charge l'image */
    }
}

/* ===== LIBÉRATION DES SPRITES JOUEUR ===== */
void libererSprites() {
    int i; /* Variable de boucle */
    for (i = 0; i < NB_IDLE; i++)  if (anim_idle[i])  destroy_bitmap(anim_idle[i]);  /* Libère idle */
    for (i = 0; i < NB_RUN; i++)   if (anim_run[i])   destroy_bitmap(anim_run[i]);   /* Libère run */
    for (i = 0; i < NB_SHOOT; i++) if (anim_shoot[i]) destroy_bitmap(anim_shoot[i]); /* Libère shoot */
    for (i = 0; i < NB_DEAD; i++)  if (anim_dead[i])  destroy_bitmap(anim_dead[i]);  /* Libère dead */
}

/* ===== SPRITES DE L'ÉCLAIR ===== */
static BITMAP *anim_eclair[NB_FRAMES_ECLAIR]; /* Images de l'animation éclair */

/* ===== CHARGEMENT DES SPRITES ÉCLAIR ===== */
void chargerSpritesEclair() {
    int i;         /* Variable de boucle */
    char nom[200]; /* Nom du fichier */
    for (i = 0; i < NB_FRAMES_ECLAIR; i++) {
        sprintf(nom, "sprites/eclair2 (%d).bmp", i+1); /* On construit le nom du fichier */
        anim_eclair[i] = load_bitmap(nom, NULL);         /* On charge l'image */
    }
}

/* ===== LIBÉRATION DES SPRITES ÉCLAIR ===== */
void libererSpritesEclair() {
    int i; /* Variable de boucle */
    for (i = 0; i < NB_FRAMES_ECLAIR; i++)
        if (anim_eclair[i]) destroy_bitmap(anim_eclair[i]); /* On libère chaque image */
}

/* ===== SPRITES DU BOSS ===== */
static BITMAP *boss_attack[NB_ATTACK_BOSS]; /* Images de l'animation d'attaque du boss */
static BITMAP *boss_die[NB_DIE_BOSS];       /* Images de l'animation de mort du boss */
static BITMAP *boss_hurt[NB_HURT_BOSS];     /* Images de l'animation de dégâts du boss */
static BITMAP *boss_idle[NB_IDLE_BOSS];     /* Image de l'animation idle du boss */

/* ===== CHARGEMENT DES SPRITES BOSS ===== */
void chargerSpritesBoss() {
    int i;         /* Variable de boucle */
    char nom[200]; /* Nom du fichier */

    /* On charge les frames d'attaque */
    for (i = 0; i < NB_ATTACK_BOSS; i++) {
        sprintf(nom, "sprites/slime-attack-%d.bmp", i); /* On construit le nom */
        boss_attack[i] = load_bitmap(nom, NULL);          /* On charge l'image */
    }

    /* On charge les frames de mort */
    for (i = 0; i < NB_DIE_BOSS; i++) {
        sprintf(nom, "sprites/slime-die-%d.bmp", i); /* On construit le nom */
        boss_die[i] = load_bitmap(nom, NULL);          /* On charge l'image */
    }

    /* On charge les frames de dégâts */
    for (i = 0; i < NB_HURT_BOSS; i++) {
        sprintf(nom, "sprites/slime-hurt-%d.bmp", i); /* On construit le nom */
        boss_hurt[i] = load_bitmap(nom, NULL);          /* On charge l'image */
    }

    /* On charge la frame idle */
    boss_idle[0] = load_bitmap("sprites/slime-idle-0.bmp", NULL); /* On charge l'image idle */
}

/* ===== LIBÉRATION DES SPRITES BOSS ===== */
void libererSpritesBoss() {
    int i; /* Variable de boucle */
    for (i = 0; i < NB_ATTACK_BOSS; i++) if (boss_attack[i]) destroy_bitmap(boss_attack[i]); /* Libère attack */
    for (i = 0; i < NB_DIE_BOSS; i++)    if (boss_die[i])    destroy_bitmap(boss_die[i]);    /* Libère die */
    for (i = 0; i < NB_HURT_BOSS; i++)   if (boss_hurt[i])   destroy_bitmap(boss_hurt[i]);   /* Libère hurt */
    if (boss_idle[0]) destroy_bitmap(boss_idle[0]);                                            /* Libère idle */
}

/* ===== FONDS DE NIVEAU ===== */
/* IMPORTANT : doit être déclaré AVANT dessinerFond qui l'utilise */
static BITMAP *fonds[4]; /* Un fond par niveau */

/* ===== CHARGEMENT DES FONDS ===== */
void chargerFonds() {
    fonds[0] = load_bitmap("sprites/fond1.bmp", NULL); /* Fond niveau 1 */
    fonds[1] = load_bitmap("sprites/fond2.bmp", NULL); /* Fond niveau 2 */
    fonds[2] = load_bitmap("sprites/fond3.bmp", NULL); /* Fond niveau 3 */
    fonds[3] = load_bitmap("sprites/fond4.bmp", NULL); /* Fond niveau 4 */
}

/* ===== LIBÉRATION DES FONDS ===== */
void libererFonds() {
    int i; /* Variable de boucle */
    for (i = 0; i < 4; i++)
        if (fonds[i]) destroy_bitmap(fonds[i]); /* On libère chaque fond */
}

/* ===== AFFICHER DU TEXTE EN GRAND ===== */
static void grand_texte(BITMAP *ecran, const char *texte, int x_centre, int y_centre, int couleur, int taille) {
    int largeur;   /* Largeur du texte en pixels */
    int hauteur;   /* Hauteur du texte en pixels */
    int pos_x;     /* Position x où coller le texte agrandi */
    int pos_y;     /* Position y où coller le texte agrandi */
    BITMAP *petit; /* Petit bitmap où on dessine le texte original */

    largeur = text_length(font, texte);              /* On mesure la largeur du texte */
    hauteur = text_height(font);                     /* On mesure la hauteur du texte */
    petit = create_bitmap(largeur + 2, hauteur + 2); /* On crée un bitmap de la taille du texte */
    clear_to_color(petit, NOIR);                     /* On remplit ce bitmap en noir */
    textout_ex(petit, font, texte, 1, 1, couleur, NOIR); /* On écrit le texte dessus */
    pos_x = x_centre - (largeur * taille) / 2;      /* On calcule la position x pour centrer */
    pos_y = y_centre - (hauteur * taille) / 2;      /* On calcule la position y pour centrer */
    stretch_blit(petit, ecran,                       /* On copie le bitmap agrandi vers l'écran */
        0, 0, petit->w, petit->h,                   /* Source : tout le petit bitmap */
        pos_x, pos_y,                                /* Destination : position calculée */
        largeur * taille, hauteur * taille);         /* Taille finale agrandie */
    destroy_bitmap(petit);                           /* On libère le petit bitmap */
}

/* ===== DESSINER LE FOND ===== */
static void dessinerFond(BITMAP *ecran, int niveau) {
    int sol_y = SCREEN_H - SOL_HAUTEUR; /* Position du sol */
    int i;    /* Variable de boucle pour le dégradé */
    int bleu; /* Composante bleue pour le dégradé de secours */

    /* Si le fond du niveau est chargé, on l'affiche */
    if (niveau >= 1 && niveau <= 4 && fonds[niveau - 1]) {
        blit(fonds[niveau - 1], ecran, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche le fond */
    } else {
        /* Si pas de fond chargé, on dessine le fond étoilé de secours */
        for (i = 0; i < SCREEN_H; i++) {
            bleu = 10 + (i * 40) / SCREEN_H;                    /* Plus bleu vers le bas */
            hline(ecran, 0, i, SCREEN_W, makecol(0, 0, bleu));  /* On dessine la ligne */
        }
        for (i = 0; i < NB_ETOILES; i++) {
            int pos_x = (i * 137 + 42) % SCREEN_W;                              /* Position x étoile */
            int pos_y = (i * 97 + 13) % (SCREEN_H - HUD_HAUTEUR) + HUD_HAUTEUR; /* Position y étoile */
            putpixel(ecran, pos_x, pos_y, BLANC);                                /* On dessine l'étoile */
        }
    }

    /* On dessine le sol marron par-dessus le fond */
    rectfill(ecran, 0, sol_y, SCREEN_W, SCREEN_H, makecol(60, 35, 15)); /* Sol marron */
    hline(ecran, 0, sol_y, SCREEN_W, makecol(120, 70, 30));             /* Bord du sol */
}

/* ===== DESSINER LA BARRE D'INFO (HUD) ===== */
static void dessinerHUD(BITMAP *ecran, Partie *p) {
    char texte_score[20];  /* Texte pour afficher le score */
    char texte_niveau[20]; /* Texte pour afficher le niveau */
    char texte_temps[20];  /* Texte pour afficher le temps */
    int temps_entier;      /* Le temps arrondi à l'entier */
    int couleur_temps;     /* Couleur du temps : blanc ou rouge selon l'urgence */

    rectfill(ecran, 0, 0, SCREEN_W, HUD_HAUTEUR, makecol(10, 10, 30)); /* Fond sombre du HUD */
    rectfill(ecran, 0, HUD_HAUTEUR - 3, SCREEN_W, HUD_HAUTEUR, JAUNE); /* Ligne dorée en bas */

    /* Score à gauche */
    textout_ex(ecran, font, "SCORE", 20, 8, GRIS_CLAIR, -1);  /* Label SCORE */
    sprintf(texte_score, "%06d", p->score);                    /* Formatage sur 6 chiffres */
    grand_texte(ecran, texte_score, 68, 33, JAUNE, 2);        /* Score en grand */

    /* Niveau au centre */
    textout_ex(ecran, font, "NIVEAU", SCREEN_W/2 - 25, 8, GRIS_CLAIR, -1); /* Label NIVEAU */
    sprintf(texte_niveau, "%d / 4", p->niveau);                              /* Formatage */
    grand_texte(ecran, texte_niveau, SCREEN_W/2, 33, JAUNE, 2);             /* Niveau en grand */

    /* Temps à droite */
    temps_entier = (int)p->temps;                                          /* Arrondi du temps */
    if (temps_entier > 20) couleur_temps = BLANC;                          /* Blanc si suffisant */
    else                   couleur_temps = ROUGE_CLAIR;                    /* Rouge si urgent */
    textout_ex(ecran, font, "TEMPS", SCREEN_W - 75, 8, GRIS_CLAIR, -1);  /* Label TEMPS */
    sprintf(texte_temps, "%02d", temps_entier);                            /* Formatage */
    grand_texte(ecran, texte_temps, SCREEN_W - 45, 33, couleur_temps, 2); /* Temps en grand */

    /* Pseudo du joueur en bas */
    textprintf_ex(ecran, font, 10, SCREEN_H - 20, GRIS_CLAIR, -1, "Joueur : %s", p->pseudo);
}

/* ===== DESSINER LE JOUEUR (SPACE MARINE) ===== */
static void dessinerJoueur(BITMAP *ecran, int x, int y, int compteur, int etat) {
    BITMAP *image = NULL; /* L'image à afficher */
    int numero_image;     /* Le numéro de l'image dans l'animation */
    int largeur_sprite;   /* Largeur du sprite agrandi */
    int hauteur_sprite;   /* Hauteur du sprite agrandi */
    int pos_x;            /* Position x où afficher le sprite */
    int pos_y;            /* Position y où afficher le sprite */
    BITMAP *agrandi;      /* Le sprite agrandi avec fond transparent */

    /* On choisit quelle animation afficher selon l'état du joueur */
    if (etat == ETAT_DEAD) {
        numero_image = (compteur / 8) % NB_DEAD;  /* On change d'image toutes les 8 frames */
        image = anim_dead[numero_image];           /* On prend l'image de mort */
    } else if (etat == ETAT_SHOOT) {
        numero_image = (compteur / 4) % NB_SHOOT; /* On change d'image toutes les 4 frames */
        image = anim_shoot[numero_image];          /* On prend l'image de tir */
    } else if (etat == ETAT_RUN) {
        numero_image = (compteur / 6) % NB_RUN;   /* On change d'image toutes les 6 frames */
        image = anim_run[numero_image];            /* On prend l'image de course */
    } else {
        numero_image = (compteur / 10) % NB_IDLE; /* On change d'image toutes les 10 frames */
        image = anim_idle[numero_image];           /* On prend l'image immobile */
    }

    if (image) {
        largeur_sprite = image->w * ECHELLE_SPRITE;              /* On calcule la largeur agrandie */
        hauteur_sprite = image->h * ECHELLE_SPRITE;              /* On calcule la hauteur agrandie */
        pos_x = x - largeur_sprite / 2;                          /* Position x : centré sur x */
        pos_y = y - hauteur_sprite;                              /* Position y : bas du sprite sur y */
        agrandi = create_bitmap(largeur_sprite, hauteur_sprite); /* On crée le bitmap agrandi */
        clear_to_color(agrandi, makecol(255, 0, 255));           /* Fond magenta = transparent */
        stretch_blit(image, agrandi,                              /* On agrandit le sprite */
            0, 0, image->w, image->h,                            /* Source : tout le sprite */
            0, 0, largeur_sprite, hauteur_sprite);               /* Destination : taille agrandie */
        draw_sprite(ecran, agrandi, pos_x, pos_y);               /* On affiche le sprite */
        destroy_bitmap(agrandi);                                  /* On libère la mémoire */
    } else {
        rectfill(ecran, x - 10, y - 30, x + 10, y, BLEU); /* Carré bleu de secours */
    }
}

/* ===== DESSINER LE BOSS ===== */
static void dessinerBoss(BITMAP *ecran, Partie *p) {
    BITMAP *img_boss = NULL; /* Image du boss à afficher */
    int num_frame;           /* Numéro de la frame d'animation */
    int largeur_boss;        /* Largeur du boss agrandi */
    int hauteur_boss;        /* Hauteur du boss agrandi */
    int pos_x_boss;          /* Position x du boss */
    int pos_y_boss;          /* Position y du boss */
    BITMAP *boss_agrandi;    /* Bitmap agrandi du boss */
    int k;                   /* Variable de boucle pour la barre de vie */

    /* On choisit l'animation selon l'état du boss */
    if (p->boss.etat == BOSS_DIE) {
        num_frame = (p->boss.frame / 8) % NB_DIE_BOSS;    /* Animation mort : lente */
        img_boss = boss_die[num_frame];                     /* On prend l'image de mort */
    } else if (p->boss.etat == BOSS_HURT) {
        num_frame = (p->boss.frame / 4) % NB_HURT_BOSS;   /* Animation dégâts : rapide */
        img_boss = boss_hurt[num_frame];                    /* On prend l'image de dégâts */
    } else if (p->boss.etat == BOSS_ATTACK) {
        num_frame = (p->boss.frame / 4) % NB_ATTACK_BOSS; /* Animation attaque : rapide */
        img_boss = boss_attack[num_frame];                  /* On prend l'image d'attaque */
    } else {
        img_boss = boss_idle[0]; /* Image idle par défaut */
    }

    /* On affiche le boss agrandi */
    if (img_boss) {
        largeur_boss = img_boss->w * ECHELLE_BOSS;              /* Largeur agrandie */
        hauteur_boss = img_boss->h * ECHELLE_BOSS;              /* Hauteur agrandie */
        pos_x_boss = (int)p->boss.x - largeur_boss / 2;        /* Centré sur x */
        pos_y_boss = (int)p->boss.y - hauteur_boss / 2;        /* Centré sur y */
        boss_agrandi = create_bitmap(largeur_boss, hauteur_boss); /* On crée le bitmap */
        clear_to_color(boss_agrandi, makecol(255, 0, 255));      /* Fond magenta = transparent */
        stretch_blit(img_boss, boss_agrandi,                      /* On agrandit le boss */
            0, 0, img_boss->w, img_boss->h,                      /* Source */
            0, 0, largeur_boss, hauteur_boss);                   /* Destination */
        draw_sprite(ecran, boss_agrandi, pos_x_boss, pos_y_boss); /* On affiche le boss */
        destroy_bitmap(boss_agrandi);                              /* On libère la mémoire */

        /* On affiche la barre de vie du boss en haut de l'écran */
        rectfill(ecran, 250, 10, 550, 25, makecol(50, 0, 0));    /* Fond rouge foncé */
        for (k = 0; k < p->boss.vie; k++) {                       /* Pour chaque vie restante */
            rectfill(ecran,
                252 + k * 58, 12,    /* Position x de la vie */
                308 + k * 58, 23,    /* Position y de la vie */
                makecol(255, 0, 0)); /* Rectangle rouge vif */
        }
        textout_ex(ecran, font, "BOSS", 215, 13, BLANC, -1); /* Label BOSS */
    }
}

/* ===== DESSINER UNE BULLE ===== */
static void dessinerBulle(BITMAP *ecran, int x, int y, int rayon) {
    circlefill(ecran, x, y, rayon, makecol(200, 20, 20));                       /* Corps rouge foncé */
    circlefill(ecran, x, y, rayon - 2, makecol(230, 50, 50));                   /* Couche plus claire */
    circle(ecran, x, y, rayon, makecol(255, 120, 120));                         /* Contour rose */
    circlefill(ecran, x - rayon/3, y - rayon/3, rayon/5, makecol(255,180,180)); /* Reflet */
    circlefill(ecran, x - rayon/3, y - rayon/3, rayon/8, BLANC);               /* Centre brillant */
}

/* ===== DESSINER LE PROJECTILE ===== */
static void dessinerProjectile(BITMAP *ecran, int x, int y) {
    rectfill(ecran, x - 2, y - 20, x + 2, y, JAUNE); /* Trait jaune vertical */
    circlefill(ecran, x, y - 20, 4, BLANC);           /* Pointe blanche en haut */
    circlefill(ecran, x, y - 20, 2, JAUNE);           /* Centre jaune de la pointe */
}

/* ===== ÉCRAN DE JEU ===== */
void afficherEcranJeu(BITMAP *buffer, Partie *p) {
    int i;        /* Variable de boucle pour les bulles */
    int rayon;    /* Rayon de la bulle à dessiner */
    int sol_y;    /* Position y du sol */
    int joueur_x; /* Position x du joueur */

    sol_y    = SCREEN_H - SOL_HAUTEUR; /* On calcule la position du sol */
    joueur_x = (int)p->joueur.x;       /* Position x du joueur */

    dessinerFond(buffer, p->niveau); /* Étape 1 : on dessine le fond du niveau */
    dessinerHUD(buffer, p);          /* Étape 2 : on dessine la barre d'info */

    /* Étape 3 : on dessine toutes les bulles actives */
    for (i = 0; i < p->nb_bulles; i++) {
        if (!p->bulles[i].actif) continue;     /* On passe les bulles détruites */
        rayon = p->bulles[i].taille * 20;      /* Le rayon dépend de la taille */
        dessinerBulle(buffer,
            (int)p->bulles[i].x,               /* Position x de la bulle */
            (int)p->bulles[i].y,               /* Position y de la bulle */
            rayon);                             /* Rayon de la bulle */
    }

    /* Étape 4 : on dessine le projectile s'il est actif */
    if (p->proj.actif)
        dessinerProjectile(buffer,
            (int)p->proj.x,  /* Position x du projectile */
            (int)p->proj.y); /* Position y du projectile */

    /* Étape 5 : on dessine les éclairs */
    for (i = 0; i < MAX_ECLAIRS; i++) {
        int num_frame;  /* Numéro de la frame à afficher */
        BITMAP *img;    /* Image de l'éclair */
        if (!p->eclairs[i].actif) continue;                             /* On saute les inactifs */
        num_frame = (p->eclairs[i].frame / 4) % NB_FRAMES_ECLAIR;     /* On avance l'animation */
        img = anim_eclair[num_frame];                                   /* On prend la bonne frame */
        if (img)
            draw_sprite(buffer, img,
                (int)p->eclairs[i].x - img->w/2, /* Centré sur x */
                (int)p->eclairs[i].y);            /* Position y */
    }

    /* Étape 6 : on dessine le boss au niveau 4 */
    if (p->niveau == 4 && (p->boss.actif || p->boss.etat == BOSS_DIE))
        dessinerBoss(buffer, p); /* On affiche le boss avec ses animations */

    /* Étape 7 : on dessine le joueur sur le sol */
    dessinerJoueur(buffer,
        joueur_x,        /* Position x du joueur */
        sol_y + 40,      /* Le bas du sprite est posé sur le sol */
        p->frame,        /* Compteur d'animation */
        p->etat_joueur); /* État du joueur */

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On envoie tout à l'écran */
}

/* ===== MENU PRINCIPAL ===== */
void afficherMenu(BITMAP *buffer, int option) {
    int i;      /* Variable de boucle */
    int pos_y;  /* Position y de chaque option du menu */
    int bleu;   /* Composante bleue pour le dégradé */
    char *options[] = {
        "Nouvelle partie", /* Option 0 : nouvelle partie */
        "Reprendre",       /* Option 1 : reprendre une sauvegarde */
        "Regles du jeu",   /* Option 2 : voir les règles */
        "Quitter"          /* Option 3 : quitter le jeu */
    };

    /* Fond dégradé bleu nuit */
    for (i = 0; i < SCREEN_H; i++) {
        bleu = 15 + (i * 35) / SCREEN_H;                        /* Composante bleue */
        hline(buffer, 0, i, SCREEN_W, makecol(0, 0, bleu));     /* Ligne du dégradé */
    }

    /* Étoiles de fond */
    for (i = 0; i < 150; i++)
        putpixel(buffer,
            (i * 173 + 57) % SCREEN_W,  /* Position x de l'étoile */
            (i * 113 + 29) % SCREEN_H,  /* Position y de l'étoile */
            BLANC);                       /* Couleur blanche */

    /* Titre */
    grand_texte(buffer, "SUPER BULLES", SCREEN_W/2 + 3, SCREEN_H/6 + 3, NOIR, 3);  /* Ombre noire */
    grand_texte(buffer, "SUPER BULLES", SCREEN_W/2, SCREEN_H/6, JAUNE, 3);          /* Titre jaune */
    hline(buffer, SCREEN_W/4, SCREEN_H/6 + 35, 3*SCREEN_W/4, JAUNE);               /* Ligne déco */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/6 + 50, GRIS_CLAIR, -1,
        "Les bulles envahissent la Terre... Alex est notre dernier espoir.");

    /* Les 4 options du menu */
    for (i = 0; i < 4; i++) {
        pos_y = SCREEN_H/2 - 20 + i * 55;                                                           /* Position y */
        if (i == option)
            rectfill(buffer, SCREEN_W/2-160, pos_y-15, SCREEN_W/2+160, pos_y+25, makecol(30,30,80)); /* Fond bleu */
        else
            rectfill(buffer, SCREEN_W/2-160, pos_y-15, SCREEN_W/2+160, pos_y+25, makecol(10,10,30)); /* Fond noir */
        rect(buffer, SCREEN_W/2-160, pos_y-15, SCREEN_W/2+160, pos_y+25, JAUNE); /* Bordure jaune */
        grand_texte(buffer, options[i], SCREEN_W/2, pos_y+5, JAUNE, 2);           /* Texte option */
        if (i == option)
            triangle(buffer,
                SCREEN_W/2-175, pos_y-5,   /* Sommet haut */
                SCREEN_W/2-175, pos_y+15,  /* Sommet bas */
                SCREEN_W/2-162, pos_y+5,   /* Pointe droite */
                JAUNE);                     /* Triangle jaune */
    }

    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H-25, GRIS, -1,
        "Utilisez les fleches et Entree pour naviguer"); /* Instruction */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche le menu */
}

/* ===== ÉCRAN D'INTRO ===== */
void afficherIntro(BITMAP *buffer) {
    int i;    /* Variable de boucle */
    int bleu; /* Composante bleue pour le dégradé */

    for (i = 0; i < SCREEN_H; i++) {
        bleu = 15 + (i * 20) / SCREEN_H;
        hline(buffer, 0, i, SCREEN_W, makecol(0, 0, bleu)); /* Dégradé bleu */
    }
    for (i = 0; i < 100; i++)
        putpixel(buffer, (i*157+43)%SCREEN_W, (i*89+17)%SCREEN_H, BLANC); /* Étoiles */

    grand_texte(buffer, "SUPER BULLES", SCREEN_W/2+2, 72, NOIR, 3);  /* Ombre du titre */
    grand_texte(buffer, "SUPER BULLES", SCREEN_W/2, 70, JAUNE, 3);   /* Titre */
    hline(buffer, SCREEN_W/5, 100, 4*SCREEN_W/5, JAUNE);             /* Séparateur */

    grand_texte(buffer, "HISTOIRE", SCREEN_W/2, 130, BLEU_CLAIR, 2); /* Section histoire */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 165, BLANC, -1, "En 2047, une experience scientifique tourne mal.");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 185, BLANC, -1, "Des bulles d'energie instable envahissent les villes.");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 205, BLANC, -1, "Elles se multiplient, se divisent, et menacent tout le monde.");
    hline(buffer, SCREEN_W/4, 230, 3*SCREEN_W/4, GRIS); /* Séparateur */

    grand_texte(buffer, "VOTRE MISSION", SCREEN_W/2, 265, JAUNE, 2); /* Section mission */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 300, BLANC, -1, "Vous incarnez Alex, technicien d'elite du projet B.U.L.L.E.");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 320, BLANC, -1, "Armez-vous de votre canon et eliminez toutes les bulles.");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 340, BLANC, -1, "4 zones a nettoyer. Ne vous faites pas toucher.");
    hline(buffer, SCREEN_W/4, 370, 3*SCREEN_W/4, GRIS); /* Séparateur */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 400, GRIS_CLAIR, -1, "Une bulle touchee se divise. La plus petite disparait.");

    grand_texte(buffer, "ENTREE pour commencer", SCREEN_W/2, SCREEN_H-35, JAUNE, 2); /* Instruction */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche l'intro */
}

/* ===== ÉCRAN DES RÈGLES ===== */
void afficherRegles(BITMAP *buffer) {
    int i;    /* Variable de boucle */
    int bleu; /* Composante bleue pour le dégradé */

    for (i = 0; i < SCREEN_H; i++) {
        bleu = 20 + (i * 20) / SCREEN_H;
        hline(buffer, 0, i, SCREEN_W, makecol(5, 5, bleu)); /* Dégradé bleu foncé */
    }

    grand_texte(buffer, "REGLES DU JEU", SCREEN_W/2+2, 52, NOIR, 2); /* Ombre */
    grand_texte(buffer, "REGLES DU JEU", SCREEN_W/2, 50, JAUNE, 2);  /* Titre */
    hline(buffer, SCREEN_W/5, 75, 4*SCREEN_W/5, JAUNE);               /* Séparateur */

    grand_texte(buffer, "CONTROLES", SCREEN_W/2, 110, BLEU_CLAIR, 2); /* Section contrôles */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 140, GRIS_CLAIR, -1, "Fleche gauche / droite : deplacer Alex");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 160, GRIS_CLAIR, -1, "ESPACE : tirer");
    hline(buffer, SCREEN_W/4, 185, 3*SCREEN_W/4, GRIS); /* Séparateur */

    grand_texte(buffer, "OBJECTIF", SCREEN_W/2, 215, BLEU_CLAIR, 2); /* Section objectif */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 245, GRIS_CLAIR, -1, "Eliminez toutes les bulles avant la fin du temps.");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 265, GRIS_CLAIR, -1, "Une bulle touchee se divise en 2 plus petites.");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 285, GRIS_CLAIR, -1, "La plus petite bulle disparait quand elle est touchee.");
    hline(buffer, SCREEN_W/4, 310, 3*SCREEN_W/4, GRIS); /* Séparateur */

    grand_texte(buffer, "VOUS PERDEZ SI...", SCREEN_W/2, 340, ROUGE_CLAIR, 2); /* Section défaite */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 370, ROUGE_CLAIR, -1, "Une bulle vous touche");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 390, ROUGE_CLAIR, -1, "Le temps s'ecoule completement");

    grand_texte(buffer, "ECHAP pour revenir", SCREEN_W/2, SCREEN_H-30, GRIS, 2); /* Instruction */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche les règles */
}

/* ===== ÉCRAN DE VICTOIRE ===== */
void afficherVictoire(BITMAP *buffer, int score) {
    int i;          /* Variable de boucle */
    int vert;       /* Composante verte pour le dégradé */
    char texte[20]; /* Pour afficher le score */

    for (i = 0; i < SCREEN_H; i++) {
        vert = (i * 40) / SCREEN_H;
        hline(buffer, 0, i, SCREEN_W, makecol(0, vert, 0)); /* Dégradé vert */
    }

    grand_texte(buffer, "VICTOIRE !", SCREEN_W/2+3, SCREEN_H/2-83, NOIR, 3);   /* Ombre */
    grand_texte(buffer, "VICTOIRE !", SCREEN_W/2, SCREEN_H/2-85, JAUNE, 3);    /* Titre */
    hline(buffer, SCREEN_W/4, SCREEN_H/2-55, 3*SCREEN_W/4, JAUNE);            /* Séparateur */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2-30, BLANC, -1,
        "Alex a sauve la Terre ! Les bulles sont vaincues !");
    sprintf(texte, "Score : %d", score);                                        /* Formatage du score */
    grand_texte(buffer, texte, SCREEN_W/2, SCREEN_H/2+20, JAUNE, 2);          /* Score en grand */
    grand_texte(buffer, "ENTREE pour continuer", SCREEN_W/2, SCREEN_H-40, GRIS_CLAIR, 2); /* Instruction */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche la victoire */
}

/* ===== ÉCRAN DE DÉFAITE ===== */
void afficherDefaite(BITMAP *buffer) {
    int i;     /* Variable de boucle */
    int rouge; /* Composante rouge pour le dégradé */

    for (i = 0; i < SCREEN_H; i++) {
        rouge = (i * 35) / SCREEN_H;
        hline(buffer, 0, i, SCREEN_W, makecol(rouge, 0, 0)); /* Dégradé rouge */
    }

    grand_texte(buffer, "GAME OVER", SCREEN_W/2+3, SCREEN_H/2-83, NOIR, 3);      /* Ombre */
    grand_texte(buffer, "GAME OVER", SCREEN_W/2, SCREEN_H/2-85, ROUGE_CLAIR, 3); /* Titre */
    hline(buffer, SCREEN_W/4, SCREEN_H/2-55, 3*SCREEN_W/4, ROUGE_CLAIR);         /* Séparateur */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2-25, BLANC, -1, "Alex n'a pas survecu...");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2+5, GRIS_CLAIR, -1,
        "Les bulles continuent de proliferer sur Terre.");
    grand_texte(buffer, "R = Recommencer    ECHAP = Menu", SCREEN_W/2, SCREEN_H-40, JAUNE, 2); /* Instruction */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche la défaite */
}

/* ===== DÉCOMPTE AVANT LE NIVEAU ===== */
void afficherDecompte(BITMAP *buffer, int chiffre, int niveau) {
    char texte[2]; /* Pour stocker le chiffre en texte */
    dessinerFond(buffer, niveau); /* On dessine le fond du niveau */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2-60, BLANC, -1, "Preparez-vous !"); /* Message */
    sprintf(texte, "%d", chiffre);                                                                  /* Conversion */
    grand_texte(buffer, texte, SCREEN_W/2, SCREEN_H/2, JAUNE, 6);                                 /* Chiffre en grand */
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche le décompte */
}