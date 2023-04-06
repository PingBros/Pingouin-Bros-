#ifndef COORDONNEES_H_
#define COORDONNEES_H_
#include "coordonnees.h"
#endif 
#include <stdio.h>
#include <stdlib.h>

#define MAXCAR 100
/**
 * \file item.h
 * \brief Fichier pour la structure item
 * \author Antoine Teissier & Lucas Barbet
 * \version 1
 * \date 9 Février 2023
 * 
*/

/**
 * \struct item_s
 * \brief Structure pour un item
 */
typedef struct item_s {
    char * nom; /**<nom de l'item */
    int boost[6];/**<statisques de l'item*/
    coordonnees_t coord;/**<valeur de ses coordonnées */
} item_t;

extern void affiche_item(item_t * item);
extern item_t * creation_item(char * nom, int vie, int degats, int vitesse_d, int vitesse_a, int defense, int saut);
extern void destruction_item(item_t ** item);
extern void sauvegarder_item(item_t *item, char *nomDossier);
extern void charger_item(item_t *item,char * nomDossier);
