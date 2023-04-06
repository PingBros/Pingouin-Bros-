#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define PINGOUIN_Y_SAUT 320

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define POS_PING_SOL SCREEN_HEIGHT - 100

#define FALSE 0
#define TRUE 1

#define MAX_ITEMS 5


/*
 * Prototypes des fonctions
 */
int init_win();
int init_events();
int init_bg_jeu_windows();
int init_ennemy();
int menu_principal();
int jeu_window();
void affiche_rendu_saut();
void affiche_rendu();

int choixdep_ennemy(int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy);
int events_dep(int en_mvmt, int sauter , int attaquer);