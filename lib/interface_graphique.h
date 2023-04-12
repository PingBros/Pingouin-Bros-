#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define LARGEUR_TILE 24 // largeur des tiles.
#define HAUTEUR_TILE 16 // hauteur des tiles

#define END 50

#define NOMBRE_BLOCS_LARGEUR 15 // nombre a afficher en fin et y
#define NOMBRE_BLOCS_HAUTEUR 13
#define MAXCAR_MAP 500

#define TRUE 1
#define FALSE 0

/**
 * \file interface_graphique.h
 * \brief Librairie avec les bibliothèques, constantes et prototypes de fonctions nécessaire à l'interface graphique
 * \author Chevallier Hugo et Patault Kylian
 * \version 1
 * \date 9 Avril 2023
 *
 */

/**
 * \struct map_s
 * \brief Structure pour la génération de la map
 */
typedef struct map_s
{
    int largeur;
    int hauteur;
    char *table[MAXCAR_MAP];
} map_t;

/*
 * Prototypes des fonctions
 */

void charger_map(map_t *carte, char *chemin);
void seconde_map(map_t *map, char *s_map[]);
void Afficher(SDL_Renderer *renderer, SDL_Texture *tileset, map_t *map, SDL_Texture *perso, SDL_Texture *home_texture, int deb, int fin);
int menu_principal();
int jeu();
int detect_obstacle(map_t *map);
void deplacements(map_t *map, int avancer, int reculer, int sauter);
int detectCollision(SDL_Rect rect1, SDL_Rect rect2);