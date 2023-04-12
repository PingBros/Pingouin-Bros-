#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/pingouin.h"

#define TRUE 1
#define FALSE 0

/**
 * \file pingouin.c
 * \brief Fichier pour les fonctions pingouin
 * \author Projet Pingouin Bros
 * \version 1
 * \date 10 Février 2023
 *
 */

/**
 * \fn void afficher_pingouin(pingouin_t * ping)
 * \brief Fonction d'affichage des stats et des items du pingouin
 *
 * \param ping structure pingouin
 * \return void.
 */
void afficher_pingouin(pingouin_t *ping) {
  int i;
  affiche_personnage(ping->pers);
  for (i = 0; i < ping->nb_item; i++) {
    printf("\n");
    affiche_item(ping->liste[i]);
  }
}

/**
 * \fn void creation_pingouin(pingouin_t * ping, char * nomDossier,char * pseudo) 
 * \brief Fonction de création des stats à partir d'un fichier texte et de l'item principal du pingouin
 *
 * \param ping structure pingouin
 * \param nomDossier fichier de sauvegarde des stats du futur Pingouin
 * \param pseudo pseudo du joueurs
 * \return void.
 */
void creation_pingouin(pingouin_t *ping, char *nomDossier, char *pseudo) {
  ping->pers = malloc(sizeof(personnage_t));
  charger_base(ping->pers, "../src/fich_txt/joueur.txt"); // chargement d'une base qui ne change jamais
  item_t *mains = creation_item("mains", 0, 0, 0, 0, 0, 0);
  ping->pers->nom = realloc(ping->pers->nom, strlen(pseudo) * sizeof(char) + 1);
  strcpy(ping->pers->nom, pseudo);
  ping->liste[0] = mains;
  ping->nb_item = 1;
  ping->liste[0]->coord.x = 0;
  ping->liste[0]->coord.y = 0;
  ping->cheminStatJoueur = malloc(strlen(nomDossier) * sizeof(char) + 1);
  strcpy(ping->cheminStatJoueur, nomDossier);
}

/**
 * \fn void charger_ping(pingouin_t *ping,char * nomDossier,char * pseudo,item_t,*listeG[],int nbItemG) 
 * \brief Fonction de création des stats à partir d'un fichier texte et de l'item principal du pingouin 
 * 
 * \param ping structure pingouin 
 * \param nomDossier fichier de sauvegarde des stats du futur Pingouin 
 * \param pseudo pseudo du joueurs 
 * \param listeG liste de pointeurs sur tous les items du jeu 
 * \param nbItemG nombre d'item dans le jeu 
 * \return void.
 */
void charger_ping(pingouin_t *ping, char *nomDossier, char *pseudo,item_t *listeG[3], int nbItemG) {
  FILE *data_pers = fopen("../src/fich_txt/ping.txt", "r");
  char nom[MAXCAR];
  char chemin[MAXCAR];
  int nb;
  char item[MAXCAR];

  if ((data_pers != NULL) && ((feof(data_pers))))
  {
    ping->pers = malloc(sizeof(personnage_t));
    item_t *mains = creation_item("mains", 0, 0, 0, 0, 0, 0);
    ping->liste[0] = mains;
    ping->nb_item = 1;
    ping->liste[0]->coord.x = 0;
    ping->liste[0]->coord.y = 0;
    if (!(feof(data_pers)))
    {
      fscanf(data_pers, "Pseudo=%s\n", nom);
      fscanf(data_pers, "Chemin_Stat_Joueur=%s\n", chemin);
      fscanf(data_pers, "NombreItem=%i\n", &nb);
      for (int i = 1; i < nb + 1; i++)
      {
        fscanf(data_pers, "Nom=%s\n", item);
        for (int j = 0; j < nbItemG; j++)
        {
          if (strcmp(item, listeG[j]->nom) == 0)
          {
            ping->liste[i] = listeG[j];
          }
        }
      }
      charger_base(ping->pers, chemin);
      ping->cheminStatJoueur = malloc(strlen(chemin) * sizeof(char) + 1);
      strcpy(ping->cheminStatJoueur, chemin);
      ping->nb_item += nb;
    }
  }
  else
  {
    creation_pingouin(ping, nomDossier, pseudo);
  }
 if(ping->pers->vie==0){
   creation_pingouin(ping, nomDossier, pseudo);
 }
 fclose(data_pers);
}


/**
 * \fn sauvegarder_ping(pingouin_t *ping)
 * \brief sauvegarde les données d'un joueur
 * \param ping joueur que l'on veut sauvegarder
 */
void sauvegarder_ping(pingouin_t *ping) {
 FILE *data_pers = fopen("../src/fich_txt/ping.txt", "w");
 sauvegarder_base(ping->pers, ping->cheminStatJoueur);
 if (data_pers != NULL)
 {
   if (!(feof(data_pers)))
   {
      fprintf(data_pers, "Pseudo=%s\n", ping->pers->nom);
      fprintf(data_pers, "Chemin_Stat_Joueur=%s\n", ping->cheminStatJoueur);

      fprintf(data_pers, "NombreItem=%i\n", ping->nb_item - 1);

      for (int i = 1; i < ping->nb_item; i++)
      {
        fprintf(data_pers, "Nom=%s\n", ping->liste[i]->nom);
      }
   }
 }
  fclose(data_pers);
}

/**
 * \fn void appliquer_items(pingouin_t * ping)
 * \brief Fonction pour appliquer les boosts des items au pingouin
 *
 * \param ping structure pingouin
 * \return void.
 */
void appliquer_items(pingouin_t *ping) {
  int i, j;
  for (i = 0; i < ping->nb_item; i++) {
    for (j = 0; j < 6; j++) {
      switch (j) {
      case 0:
        ping->pers->vie += ping->liste[i]->boost[j];
        break;
      case 1:
        ping->pers->degats += ping->liste[i]->boost[j];
        break;
      case 2:
        ping->pers->vitesse_d += ping->liste[i]->boost[j];
        break;
      case 3:
        ping->pers->vitesse_a += ping->liste[i]->boost[j];
        break;
      case 4:
        ping->pers->defense += ping->liste[i]->boost[j];
        break;
      case 5:
        ping->pers->saut += ping->liste[i]->boost[j];
        break;
      }
    }
  }
}

/**
 * \fn void retirer_items(pingouin_t * ping)
 * \brief Fonction pour retirer les boosts des items au pingouin
 *
 * \param ping structure pingouin
 * \return void.
 */
void retirer_items(pingouin_t *ping) {
  int i, j;
  for (i = 0; i < ping->nb_item; i++) {
    for (j = 0; j < 6; j++) {
      switch (j) {
      case 0:
        ping->pers->vie -= ping->liste[i]->boost[j];
        break;
      case 1:
        ping->pers->degats -= ping->liste[i]->boost[j];
        break;
      case 2:
        ping->pers->vitesse_d -= ping->liste[i]->boost[j];
        break;
      case 3:
        ping->pers->vitesse_a -= ping->liste[i]->boost[j];
        break;
      case 4:
        ping->pers->defense -= ping->liste[i]->boost[j];
        break;
      case 5:
        ping->pers->saut -= ping->liste[i]->boost[j];
        break;
      }
    }
  }
}

/**
 * \fn void ajouter_item(pingouin_t * ping, item_t * item)
 * \brief Fonction d'ajout d'un item pour le pingouin
 *
 * \param ping structure pingouin
 * \param item structure item
 * \return void.
 */
void ajouter_item(pingouin_t *ping, item_t *item) {
  int i, trouve = FALSE;
  if (ping->nb_item < MAX_ITEMS) {
    for (i = 0; i < ping->nb_item; i++) {
      if (ping->liste[i] == item)
        trouve = TRUE;
    }
    if (trouve == FALSE) {
      item->coord.x = 0;
      item->coord.y = 0;
      ping->liste[ping->nb_item] = item;
      ping->nb_item++;
    }
  }
}

/**
 * \fn void supprimer_item(pingouin_t *ping, item_t *item)
 * \brief Fonction de suppression d'un item pour le pingouin
 *
 * \param ping structure pingouin
 * \param item structure item
 * \return void.
 */
void supprimer_item(pingouin_t *ping, item_t *item) {
  int i;
  for (i = 0; i < ping->nb_item; i++) {
    if (ping->liste[i]->nom == item->nom) {
      for(; i < (ping->nb_item - 1); i++) {
        ping->liste[i] = ping->liste[i + 1];
      }
      ping->nb_item--;
    }
  }
}

/**
 * \fn void destruction_pingouin(pingouin_t ** ping)
 * \brief Fonction de destruction d'un pingouin
 *
 * \param ping structure pingouin
 * \return void.
 */
extern void destruction_pingouin(pingouin_t **ping)
{
  int i;
  destruction_personnage(&((*ping)->pers));
  for (i = 0; i < (*ping)->nb_item; i++) {
    destruction_item(&(*ping)->liste[i]);
  }
  free((*ping)->cheminStatJoueur);
  free(*ping);
  (*ping) = NULL;
}


extern void calcul_degats(personnage_t *p1, personnage_t *p2){
    p2->vie -= p1->degats * (1 - (p2->defense / 100));
}

extern int vivant(personnage_t * pers){
    return pers->vie > 0;
}
