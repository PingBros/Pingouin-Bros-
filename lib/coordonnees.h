#include <stdio.h>
#include <stdlib.h>

/**
 * \file coordonnees.h
 * \brief Fichier pour la structure coordonnees
 * \author Projet Pingouin Bros
 * \version 1
 * \date 9 Février 2023
 * 
 */

/**
 * \struct coordonnees_s
 * \brief Structure pour les coordonnées
 */
typedef struct coordonnees_s {
    int x; /**<valeur de la coordonnée x */
    int y; /**<valeur de la coordonnée y */
    } coordonnees_t;


extern void affiche_coordonnees(coordonnees_t * coord);