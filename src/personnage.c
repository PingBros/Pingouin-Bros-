#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/personnage.h"

#define MAXCAR 100
/**
 * \file personnage.c
 * \brief Fichier pour la gestion d'un personnage
 * \author Antoine Teissier & Lucas Barbet
 * \version 1
 * \date 9 Février 2023
 * 
 */

/**
* \fn  void affiche_personnage(personnage_t *pers) 
* \brief Affiche les states d'un personnage 
* \param pers le personnage 
*
*/
void affiche_personnage(personnage_t *pers) {
  printf("Nom : %s\n", pers->nom);
  printf("Vie : %i\n", pers->vie);
  printf("degats : %i\n", pers->degats);
  printf("vitesse deplacement : %i\n", pers->vitesse_d);
  printf("vitesse d'attaque : %i\n", pers->vitesse_a);
  printf("Defense : %i\n", pers->defense);
  printf("saut : %i\n", pers->saut);
  affiche_direction(pers->direction);
  affiche_coordonnees(&pers->coord);
}

/**
* \fn void affiche_direction(direction_t dir)
* \brief Affiche la direction
* \param dir direction a afficher 
*/
void affiche_direction(direction_t dir) {
  switch (dir) {
  case DROITE:
    printf("Droite ->\n");
    break;
  case GAUCHE:
    printf("Gauche <-\n");
    break;
  default:
    printf("Pas de direction defini\n");
    break;
  }
}

/**
* \fn void gestion_stat(int * stat, int valeur)
* \brief boost une stat
* \param stat stat a boost
* \param valeur valeur du boost 
*/
void gestion_stat(int * stat, int valeur) {
  * stat += valeur;
}

/**
* \fn void charger_base(personnage_t *pers, char *nomDossier)
* \brief charge une base de stat
* \param pers personnage où il faut stocker les states 
* \param nomDossier chemin vers le ficheir avec les stats
*/
void charger_base(personnage_t *pers, char *nomDossier) {
  FILE *data_pers = fopen(nomDossier, "r");
  char nom[MAXCAR];
  int vie;
  int degats;
  int vitesse_d;
  int vitesse_a;
  int defense;
  int saut;
  int direction;
  coordonnees_t coord;
  if (data_pers != NULL) {
    if (!(feof(data_pers))) {
      fscanf(data_pers, "Nom=%s\n",nom);
      fscanf(data_pers, "Vie=%i\n", &vie);
      fscanf(data_pers, "Vie=%i\n", &vie);
      fscanf(data_pers, "Degats=%i\n", &degats);
      fscanf(data_pers, "Vitesse_d=%i\n", &vitesse_d);
      fscanf(data_pers, "Vitesse_a=%i\n", &vitesse_a);
      fscanf(data_pers, "Defense=%i\n", &defense);
      fscanf(data_pers, "Saut=%i\n", &saut);
      fscanf(data_pers, "Direction=%i\n", &direction);
      fscanf(data_pers, "X=%i Y=%i\n", &coord.x, &coord.y);
      pers->nom=malloc(strlen(nom)*sizeof(char)+1);
      strcpy(pers->nom,nom);
      pers->vie = vie;
      pers->degats = degats;
      pers->vitesse_d = vitesse_d;
      pers->vitesse_a = vitesse_a;
      pers->defense = defense;
      pers->saut = saut;
      pers->direction = direction;
      pers->coord = coord;
    }
    fclose(data_pers);
  }
}

/**
* \fn void sauvegarder_base(personnage_t *pers, char *nomDossier)
* \brief sauvegarde une base de stat
* \param pers personnage où il faut sauvegarder les stats 
* \param nomDossier chemin vers le fichier avec les stats
*/
void sauvegarder_base(personnage_t *pers, char *nomDossier) {
  FILE *data_pers = fopen(nomDossier, "w");
  // coordonnees_t coord;
  if (data_pers != NULL) {
    if (!(feof(data_pers))) {
      fprintf(data_pers, "Nom=%s\n", pers->nom);
      fprintf(data_pers, "Vie=%i\n",pers->vie);
      fprintf(data_pers, "Degats=%i\n",pers->degats);
      fprintf(data_pers, "Vitesse_d=%i\n",pers->vitesse_d);
      fprintf(data_pers, "Vitesse_a=%i\n",pers->vitesse_a);
      fprintf(data_pers, "Defense=%i\n",pers->defense);
      fprintf(data_pers, "Saut=%i\n",pers->saut);
      fprintf(data_pers, "Direction=%i\n",pers->direction);
      fprintf(data_pers, "X=%i Y=%i\n",pers->coord.x, pers->coord.y);
    }
    fclose(data_pers);
  }
}

/**
* \fn void destruction_personnage(personnage_t ** pers)
* \brief destruction d'un personnage
* \param pers structure personnage
*/
void destruction_personnage(personnage_t ** pers) {
  free((*pers)->nom);
  (*pers)->nom = NULL;
  free((*pers));
  (*pers) = NULL;
}