#include <stdio.h>
#include <stdlib.h>
#ifndef COORDONNEES_H_
#define COORDONNEES_H_
#include "coordonnees.h"
#endif

/**
 * \file personnage.h
 * \brief Fichier pour la structure personnage
 * \author Antoine Teissier & Lucas Barbet
 * \version 1
 * \date 9 Février 2023
 * 
 */

/**
 * \enum direction_s
 * \brief Pour obtenir la direction de chaque personnage, là où il regarde
 * 
 * 
 */
typedef enum direction_s { DROITE , GAUCHE } direction_t ;

/**
 * \struct personnage_s
 * \brief Structure pour chaque personnage
 * \details Cela contient la vie, les dégâts, la vitesse de déplacement, la vitesse d'attaque, la défense, la hauteur du saut, la direction et ses coordonnées.
 */
typedef struct personnage_s {
    char *nom; /**<nom du peronnage */
    int vie; /**<valeur de sa vie */
    int degats; /**<valeur de ses dégâts */
    int vitesse_d; /**<valeur de sa vitesse de déplacement */
    int vitesse_a; /**<valeur de sa vitesse d'attaque */
    int defense; /**<valeur de sa défense */
    int saut; /**<valeur de sa hauteur de saut */
    direction_t direction; /**<valeur de sa direction */
    coordonnees_t coord; /**<valeur de ses coordonnées */
} personnage_t;


extern void affiche_personnage(personnage_t * pers);
extern void affiche_direction(direction_t dir);
extern void charger_base(personnage_t * pers,char * nomDossier);
extern void sauvegarder_base(personnage_t *pers, char *nomDossier); 
extern void gestion_stat(int * stat, int valeur);
extern void destruction_personnage(personnage_t ** pers);