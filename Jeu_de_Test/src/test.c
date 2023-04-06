#include "../lib/pingouin.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define True 1
#define False 0

int main(int argc, char *argv[]) {
  int p = False, i = False, j = False, a = False;
  char opt;

  if (argc != 2) {
    printf("Nombre d'arguments incorrect, 1 arguments attendus.( option possible -a -j -i -p) \n");
    exit(1);
  }

  opt = getopt(argc, argv, "-p-i-j-a");

  if (opt == 'p')
    p = True;
  if (opt == 'i')
    i = True;
  if (opt == 'j')
    j = True;
  if (opt == 'a')
    a = True;

  printf("\n\t\tDebut du programme des tests \n\n");

  if (a)
    printf("---------------------------------------------------------");

  if (p || a) {
    printf("\n\tDébut des tests pour les personnages \n");

    personnage_t *pers = malloc(sizeof(personnage_t));
    charger_base(pers, "../src/stat/stat_test.txt"); /* Attention à l'endroit où la commande ./Prog est lancée */

    printf("\nAffichage des statistiques du personnage :\n");
    affiche_personnage(pers);

    printf("\nAugmentation de 50 de la défense du personnage \n");
    gestion_stat(&pers->defense, 50);

    printf("\n");

    printf("Affichage des statistiques du personnage après modification :\n");
    affiche_personnage(pers);
    sauvegarder_base(pers, "../src/stat/stat_test.txt");

    destruction_personnage(&pers);

    printf("\n\tFin des tests pour les personnages \n");
  }

  if (a)
    printf("---------------------------------------------------------");

  if (i || a) {
    printf("\n\tDébut des tests pour les items \n");

    item_t *epee = malloc(sizeof(item_t));
    charger_item(epee, "../src/stat/epee.txt");

    printf("\nAffichage des statistiques de l'item epee :\n");
    affiche_item(epee);

    printf("\nChangement de la vie de l'épee \n");
    epee->boost[0] = 10;

    printf("\n");

    printf("Affichage des statistiques de l'item epee après modification :\n");
    affiche_item(epee);
    sauvegarder_item(epee, "../src/stat/epee.txt");

    printf("\n");

    item_t *bouclier = creation_item("bouclier", 0, 0, -10, -15, 70, -1);
    bouclier->coord.x = 10;
    bouclier->coord.y = 15;

    printf("\nAffichage des statistiques de l'item bouclier :\n");
    affiche_item(bouclier);

    printf("\nChangement de la vitesse d'attaque du bouclier \n");
    bouclier->boost[3] = -10;

    printf("\n");

    printf(
        "Affichage des statistiques de l'item bouclier après modification :\n");
    affiche_item(bouclier);
    sauvegarder_item(bouclier, "../src/stat/bouclier.txt");

    destruction_item(&epee);
    destruction_item(&bouclier);

    printf("\n\tFin des tests pour les items \n");
  }

  if (a)
    printf("---------------------------------------------------------");

  if (j || a) {
    printf("\n\tDébut des tests pour le pingouin \n");

    int nbItemG = 3;
    item_t *listeItemG[nbItemG];
    pingouin_t *ping = malloc(sizeof(pingouin_t));

    item_t *epee = malloc(sizeof(item_t));
    charger_item(epee, "../src/stat/epee.txt");

    item_t *chaussures = malloc(sizeof(item_t));
    charger_item(chaussures, "../src/stat/chaussures.txt");
    ajouter_item(ping, chaussures);

    item_t *bouclier = malloc(sizeof(item_t));
    charger_item(bouclier, "../src/stat/bouclier.txt");

    listeItemG[0] = epee;
    listeItemG[1] = chaussures;
    listeItemG[2] = bouclier;
    charger_ping(ping, "../src/stat/pingouin.txt", "GMK", listeItemG, 3);

    printf("\nAffichage des statistiques du pingouin avant l'ajout des items chaussures & bouclier :\n");
    afficher_pingouin(ping);

    ajouter_item(ping, bouclier);

    appliquer_items(ping);

    printf("\nAffichage des statistiques du pingouin après l'ajout des items chaussures & bouclier :\n");
    afficher_pingouin(ping);

    printf("\nAffichage des statistiques du pingouin après l'enlèvement des items chaussures & bouclier :\n");
    retirer_items(ping);
    afficher_pingouin(ping);
    supprimer_item(ping,chaussures);
    printf("%i", ping->nb_item);
    /*printf("\nAugmentation de 30 des dégâts du personnage \n");
    gestion_stat(&ping->pers->degats, 30);*/

    printf("\n");

    printf("Affichage des statistiques du personnage après modification :\n");
    afficher_pingouin(ping);
    sauvegarder_ping(ping);

    destruction_item(&epee);
    destruction_item(&chaussures);
    destruction_pingouin(&ping);

    printf("\n\tFin des tests pour le pingouin \n");
  }

  if (a)
    printf("---------------------------------------------------------");

  printf("\n\t\tFin des tests \n");

  return 1;
}
