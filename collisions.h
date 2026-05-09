/*
 * collision.h
 * Header de la détection des collisions.
 * - Contient le prototype de collisionCercles()
 * - Contient le prototype de collisionRectangles()
 * - Contient le prototype de gererCollisions()
 * - Inclure ce fichier dans jeu.c
 */
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "entites.h" /* Nécessaire pour Joueur, Bulle, Projectile */

int collisionCercles(float x1, float y1, float r1, float x2, float y2, float r2); /* Teste collision entre deux cercles */
int collisionRectangles(float x1, float y1, float w1, float h1,
                        float x2, float y2, float w2, float h2);                   /* Teste collision entre deux rectangles */
void gererCollisions(Partie *p);  /* Gère toutes les collisions de la boucle de jeu */

#endif