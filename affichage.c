/*
 * affichage.c
 * Rendu graphique avec Allegro 4.
 * - Afficher une frame du jeu (joueur, bulles, projectile, HUD)
 * - Afficher le menu principal avec option en surbrillance
 * - Afficher l'écran de victoire et de défaite
 * - Afficher le score, le temps restant et le niveau
 */
#include "affichage.h" /* On importe les prototypes */

void afficherEcranJeu(BITMAP *buffer, Partie *p) { /* Reçoit le buffer et tout l'état du jeu */
    int i;                                          /* Variable de boucle */

    clear_to_color(buffer, makecol(0, 0, 0)); /* On efface l'écran en noir */

    /* Dessiner le joueur */
    if (p->joueur.vivant)  /* On dessine le joueur seulement s'il est en vie */
        rectfill(buffer,
            (int)(p->joueur.x - 10), (int)(p->joueur.y - 10), /* Coin supérieur gauche */
            (int)(p->joueur.x + 10), (int)(p->joueur.y + 10), /* Coin inférieur droit */
            makecol(0, 255, 0)); /* Le joueur est représenté par un carré vert */

    /* Dessiner les bulles */
    for (i = 0; i < p->nb_bulles; i++) {          /* On parcourt toutes les bulles */
        if (!p->bulles[i].actif) continue;         /* On saute les bulles inactives */
        int rayon = p->bulles[i].taille * 15;      /* Le rayon dépend de la taille */
        circle(buffer,
            (int)p->bulles[i].x, (int)p->bulles[i].y, /* Centre de la bulle */
            rayon, makecol(255, 0, 0));                 /* Cercle rouge */
    }

    /* Dessiner le projectile */
    if (p->proj.actif) /* On dessine le projectile seulement s'il est actif */
        rectfill(buffer,
            (int)(p->proj.x - 2), (int)(p->proj.y - 10), /* Coin supérieur */
            (int)(p->proj.x + 2), (int)(p->proj.y),       /* Coin inférieur */
            makecol(255, 255, 0)); /* Projectile en jaune */

    /* HUD : score, niveau et temps — positionnés avec SCREEN_W et SCREEN_H */
    textprintf_ex(buffer, font, 10, 10, makecol(255,255,255), -1, "Score: %d", p->score);         /* Score en haut à gauche */
    textprintf_ex(buffer, font, 10, 30, makecol(255,255,255), -1, "Niveau: %d", p->niveau);       /* Niveau en dessous */
    textprintf_ex(buffer, font, SCREEN_W - 120, 10, makecol(255,255,0), -1, "Temps: %.0f", p->temps); /* Temps en haut à droite */

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On copie le buffer sur l'écran */
}

void afficherMenu(BITMAP *buffer, int option) { /* option : 0=Nouvelle partie, 1=Reprendre, 2=Règles, 3=Quitter */
    int couleur;                                 /* Couleur de l'option selon si elle est sélectionnée */

    clear_to_color(buffer, makecol(0, 0, 0)); /* On efface l'écran en noir */

    /* Titre du jeu centré en haut */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/5,
        makecol(255, 255, 0), -1, "SUPER BULLES"); /* Titre en jaune */

    /* Option 1 : Nouvelle partie */
    couleur = (option == 0) ? makecol(255,255,255) : makecol(100,100,100); /* Blanc si sélectionné, gris sinon */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 - 60, couleur, -1, "1. Nouvelle partie");

    /* Option 2 : Reprendre */
    couleur = (option == 1) ? makecol(255,255,255) : makecol(100,100,100);
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 - 20, couleur, -1, "2. Reprendre");

    /* Option 3 : Règles du jeu */
    couleur = (option == 2) ? makecol(255,255,255) : makecol(100,100,100);
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 + 20, couleur, -1, "3. Regles du jeu");

    /* Option 4 : Quitter */
    couleur = (option == 3) ? makecol(255,255,255) : makecol(100,100,100);
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 + 60, couleur, -1, "4. Quitter");

    /* Instruction de navigation */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H - 50,
        makecol(150,150,150), -1, "Utilisez les fleches et Entree pour naviguer");

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche le menu */
}

void afficherRegles(BITMAP *buffer) { /* Affiche les règles du jeu */
    clear_to_color(buffer, makecol(0, 0, 0)); /* On efface l'écran en noir */

    textprintf_centre_ex(buffer, font, SCREEN_W/2, 50,  makecol(255,255,0), -1, "REGLES DU JEU");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 120, makecol(255,255,255), -1, "Fleche gauche/droite : se deplacer");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 160, makecol(255,255,255), -1, "Espace : tirer");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 200, makecol(255,255,255), -1, "Eliminez toutes les bulles pour gagner");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 240, makecol(255,255,255), -1, "Ne vous faites pas toucher par une bulle");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, 280, makecol(255,255,255), -1, "Respectez le temps imparti");
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H - 50,
        makecol(150,150,150), -1, "Appuyez sur Echap pour revenir au menu");

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche l'écran des règles */
}

void afficherVictoire(BITMAP *buffer, int score) { /* Reçoit le score final */
    clear_to_color(buffer, makecol(0, 0, 0)); /* On efface l'écran en noir */

    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 - 60,
        makecol(0, 255, 0), -1, "VICTOIRE !"); /* Message en vert */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2,
        makecol(255,255,255), -1, "Score final: %d", score); /* Score final */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 + 60,
        makecol(150,150,150), -1, "Appuyez sur Entree pour continuer");

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche l'écran de victoire */
}

void afficherDefaite(BITMAP *buffer) { /* Pas besoin du score ici */
    clear_to_color(buffer, makecol(0, 0, 0)); /* On efface l'écran en noir */

    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 - 60,
        makecol(255, 0, 0), -1, "GAME OVER"); /* Message en rouge */
    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 + 60,
        makecol(150,150,150), -1, "Appuyez sur Entree pour continuer");

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche l'écran de défaite */
}

void afficherDecompte(BITMAP *buffer, int chiffre) { /* chiffre = 3, 2 ou 1 */
    clear_to_color(buffer, makecol(0, 0, 0)); /* On efface l'écran en noir */

    textprintf_centre_ex(buffer, font, SCREEN_W/2, SCREEN_H/2,
        makecol(255, 255, 0), -1, "%d", chiffre); /* On affiche le chiffre en grand au centre */

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); /* On affiche le décompte */
}