/*
 * sauvegarde.c
 * Sauvegarde et chargement des parties.
 * - Écrire le pseudo et le numéro de niveau dans sauvegarde.txt
 * - Lire la sauvegarde associée à un pseudo
 * - Gérer plusieurs sauvegardes dans un même fichier
 * - Retourner -1 si aucune sauvegarde trouvée pour ce pseudo
 */
#include "sauvegarde.h" /* On importe les prototypes */
#include <stdio.h>      /* Pour FILE, fopen, fscanf, fprintf, fclose */
#include <string.h>     /* Pour strcmp() */

int sauvegarder(char *pseudo, int niveau) { /* Reçoit le pseudo et le niveau à sauvegarder */
    FILE *f;                                 /* Pointeur vers le fichier */
    char p[MAX_PSEUDO];                      /* Pseudo lu depuis le fichier */
    int niv;                                 /* Niveau lu depuis le fichier */
    int trouve = 0;                          /* 1 si on a trouvé le pseudo dans le fichier */

    /* On lit le fichier existant et on le réécrit avec la mise à jour */
    FILE *tmp = fopen("tmp.txt", "w");      /* Fichier temporaire pour réécrire */
    if (!tmp) return -1;                     /* Erreur si on ne peut pas créer le fichier */

    f = fopen(FICHIER_SAUVEGARDE, "r");     /* On ouvre le fichier de sauvegarde en lecture */
    if (f) {                                 /* Si le fichier existe */
        while (fscanf(f, "%s %d", p, &niv) == 2) { /* On lit chaque ligne */
            if (strcmp(p, pseudo) == 0) {   /* Si c'est le même pseudo */
                fprintf(tmp, "%s %d\n", pseudo, niveau); /* On écrit le nouveau niveau */
                trouve = 1;                  /* On a trouvé et mis à jour le pseudo */
            } else {
                fprintf(tmp, "%s %d\n", p, niv); /* On recopie les autres sauvegardes */
            }
        }
        fclose(f); /* On ferme le fichier de lecture */
    }

    if (!trouve) /* Si le pseudo n'était pas dans le fichier */
        fprintf(tmp, "%s %d\n", pseudo, niveau); /* On l'ajoute à la fin */

    fclose(tmp); /* On ferme le fichier temporaire */
    remove(FICHIER_SAUVEGARDE);          /* On supprime l'ancien fichier */
    rename("tmp.txt", FICHIER_SAUVEGARDE); /* On renomme le temporaire */
    return 0; /* Succès */
}

int chargerSauvegarde(char *pseudo) { /* Reçoit le pseudo à rechercher */
    FILE *f;                           /* Pointeur vers le fichier */
    char p[MAX_PSEUDO];                /* Pseudo lu depuis le fichier */
    int niv;                           /* Niveau lu depuis le fichier */

    f = fopen(FICHIER_SAUVEGARDE, "r"); /* On ouvre le fichier en lecture */
    if (!f) return -1;                   /* Si le fichier n'existe pas, retourne -1 */

    while (fscanf(f, "%s %d", p, &niv) == 2) { /* On lit chaque ligne */
        if (strcmp(p, pseudo) == 0) {   /* Si c'est le pseudo recherché */
            fclose(f);                   /* On ferme le fichier */
            return niv;                  /* On retourne le niveau trouvé */
        }
    }

    fclose(f);  /* On ferme le fichier */
    return -1;  /* Pseudo non trouvé : retourne -1 */
}
int sauvegarderMeilleurScore(int score) {
    FILE *f;                              /* Pointeur vers le fichier */
    int meilleur = 0;                     /* Meilleur score actuel */

    f = fopen("meilleur_score.txt", "r"); /* On lit le score actuel */
    if (f) {
        fscanf(f, "%d", &meilleur);       /* On lit le meilleur score */
        fclose(f);                         /* On ferme le fichier */
    }

    if (score > meilleur) {               /* Si le nouveau score est meilleur */
        f = fopen("meilleur_score.txt", "w"); /* On ouvre en écriture */
        if (!f) return -1;                 /* Erreur */
        fprintf(f, "%d\n", score);         /* On sauvegarde le nouveau meilleur */
        fclose(f);                          /* On ferme le fichier */
    }
    return 0; /* Succès */
}

int chargerMeilleurScore() {
    FILE *f;          /* Pointeur vers le fichier */
    int meilleur = 0; /* Meilleur score par défaut */

    f = fopen("meilleur_score.txt", "r"); /* On ouvre le fichier */
    if (f) {
        fscanf(f, "%d", &meilleur); /* On lit le meilleur score */
        fclose(f);                   /* On ferme le fichier */
    }
    return meilleur; /* On retourne le meilleur score */
}