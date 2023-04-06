#include <stdio.h>
#include <stdlib.h>
#include "coordonnees.h"

/**
 * \file obstacle.h
 * \brief Fichier pour la structure obstacle
 * \author Projet Pingouin Bros
 * \version 1
 * \date 9 Février 2023
 * 
 */

/**
 * \struct obstacle_s
 * \brief Structure pour un obstacle
 */
typedef struct obstacle_s {
    int hauteur;
    int longueur;
    coordonnees_t coord;
} obstacle_t;