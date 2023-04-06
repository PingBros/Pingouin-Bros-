#include <stdio.h>
#include <stdlib.h>
#include "../lib/coordonnees.h"

/**
 * \file coordonnees.c
 * \brief Fichier pour les fonctions de coordonnées
 * \author Projet Pingouin Bros
 * \version 1
 * \date 10 Février 2023
 * 
 */

/**
 * \fn void affiche_coordonnees(coordonnees_t * coord)
 * \brief Fonction d'affichage des coordonnées
 * 
 * \param coord structure coordonnées
 * \return void.
 */
void affiche_coordonnees(coordonnees_t * coord){
    printf("x = %i , y = %i\n",coord->x,coord->y);
}

