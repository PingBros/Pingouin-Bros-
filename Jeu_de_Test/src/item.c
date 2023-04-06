#include "../lib/item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * \file item.c
 * \brief Fichier pour les fonctions item
 * \author Antoine Teissier & Lucas Barbet
 * \version 1
 * \date 10 Février 2023
 *
*/

/**
 * \fn void affiche_item(item_t * item)
 * \brief Fonction d'affichage du nom, des coordonnées et des améliorations que
 * procure un item
 *
 * \param item structure item
 * \return void.
 */
void affiche_item(item_t *item) {
  int i;
  printf("%s\n", item->nom);
  for (i = 0; i < 6; i++) {
    if (item->boost[i]) {
      switch (i) {
      case 0:
        printf("Vie : %i\n", item->boost[i]);
        break;
      case 1:
        printf("Dégâts : %i\n", item->boost[i]);
        break;
      case 2:
        printf("Vitesse de déplacement : %i\n", item->boost[i]);
        break;
      case 3:
        printf("Vitesse d'attaque : %i\n", item->boost[i]);
        break;
      case 4:
        printf("Défense : %i\n", item->boost[i]);
        break;
      case 5:
        printf("Saut : %i\n", item->boost[i]);
        break;
      }
    }
  }
  affiche_coordonnees(&item->coord);
}

/**
 * \fn item_t * creation_item(char * nom, int vie, int degats, int vitesse_d, int vitesse_a, int defense, int saut) 
 * \brief Fonction de création du nom et des améliorations que procure un item
 *
 * \param nom le nom de l'item
 * \param vie la vie ajoutée / enlevée
 * \param degats les dégâts ajoutés / enlevés
 * \param vitesse_d la vitesse de déplacement ajoutée / enlevée
 * \param vitesse_a la vitesse d'attaque ajoutée / enlevée
 * \param defense la défense ajoutée / enlevée
 * \param saut la hauteur de saut ajoutée / enlevée
 * \return item
 */
item_t *creation_item(char *nom, int vie, int degats, int vitesse_d,
                      int vitesse_a, int defense, int saut) {
  item_t *item = malloc(sizeof(item_t));
  item->nom = malloc(sizeof(char) * sizeof(nom) + 1);
  strcpy(item->nom,nom);
  item->boost[0] = vie;
  item->boost[1] = degats;
  item->boost[2] = vitesse_d;
  item->boost[3] = vitesse_a;
  item->boost[4] = defense;
  item->boost[5] = saut;
  return item;
}

/**
 * \fn void destruction_item(item_t ** item) 
 * \brief Fonction de destruction d'un item
 *
 * \param item structure item
 * \return void
 */
void destruction_item(item_t ** item) {
  free((*item)->nom);
  free(*item);
  *item = NULL;
}

/**
 * \fn void charger_item(item_t *item,char * nomDossier){
 * \brief charge un item
 * \param item l'item où il faut stocker les states
 * \param nomDossier nomDossier chemin vers le fichier
 */
void charger_item(item_t *item, char *nomDossier) {
  FILE *data_item = fopen(nomDossier, "r");
  char nom[MAXCAR];
  if (data_item != NULL) {
    if (!(feof(data_item))) {
      fscanf(data_item,"Nom=%s\n",nom);
      item->nom = malloc(sizeof(char) * sizeof(nom) + 1);
      strcpy(item->nom,nom);
      fscanf(data_item,"Boost=(%i,%i,%i,%i,%i,%i) ",&item->boost[0],&item->boost[1],&item->boost[2],&item->boost[3],&item->boost[4],&item->boost[5]);
      fscanf(data_item, "X=%i Y=%i\n",&item->coord.x,&item->coord.y);
    }
    fclose(data_item);
  }
}

/**
 * \fn void sauvegarder_item(item_t *item, char *nomDossier)
 * \brief sauvegarde un item
 * \param item l'item qu'il faut sauvegarder
 * \param nomDossier chemin vers le fichier
 */
void sauvegarder_item(item_t *item, char *nomDossier) {
  FILE *data_item = fopen(nomDossier, "w");
  if (data_item != NULL) {
    if (!(feof(data_item))) {
      fprintf(data_item, "Nom=%s\n", item->nom);
      fprintf(data_item, "Boost=(%i,%i,%i,%i,%i,%i)\n", item->boost[0],
              item->boost[1], item->boost[2], item->boost[3], item->boost[4],
              item->boost[5]);
      fprintf(data_item, "X=%i Y=%i\n", item->coord.x, item->coord.y);
    }
    fclose(data_item);
  }
}
