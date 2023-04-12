//#ifndef ITEM_H_
//#define ITEM_H_
#include "item.h"
//#endif 
//#ifndef PERSONNAGE_H_
//#define PERSONNAGE_H_
#include "personnage.h"
//#endif 
#include <stdio.h>
#include <stdlib.h>

/**
 * \file pingouin.h
 * \brief Fichier pour la structure pingouin
 * \author Projet Pingouin Bros
 * \version 1
 * \date 9 Février 2023
 */

#define MAX_ITEMS 5

/**
 * \struct pingouin_s
 * \brief Structure pour le personnage Pingouin
 */
typedef struct pingouin_s {
  personnage_t *pers;
  int nb_item;
  item_t *liste[MAX_ITEMS];
  char *cheminStatJoueur;
} pingouin_t;

extern void afficher_pingouin(pingouin_t *ping);
extern void creation_pingouin(pingouin_t *ping, char *nomDossier, char *pseudo);
extern void ajouter_item(pingouin_t *ping, item_t *item);
extern void sauvegarder_ping(pingouin_t *ping);
extern void appliquer_items(pingouin_t *ping);
extern void retirer_items(pingouin_t *ping);
extern void charger_ping(pingouin_t *ping, char *nomDossier, char *pseudo, item_t *listeG[3], int nbItemG);
extern void supprimer_item(pingouin_t *ping, item_t *item);
extern void destruction_pingouin(pingouin_t **ping);
extern void calcul_degats(personnage_t *p1, personnage_t *p2);
extern int vivant(personnage_t *pers);
