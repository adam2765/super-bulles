/*
 * sauvegarde.h
 * Header de la sauvegarde et du chargement.
 * - Contient le prototype de sauvegarder()
 * - Contient le prototype de chargerSauvegarde()
 * - Les données sauvegardées : pseudo + numéro de niveau
 * - Inclure ce fichier dans jeu.c et main.c
 */
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "entites.h" /* Nécessaire pour MAX_PSEUDO */

#define FICHIER_SAUVEGARDE "sauvegarde.txt" /* Nom du fichier de sauvegarde */

int sauvegarder(char *pseudo, int niveau);   /* Écrit pseudo + niveau dans le fichier */
int chargerSauvegarde(char *pseudo);         /* Lit le niveau associé au pseudo, -1 si absent */

#endif