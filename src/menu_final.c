#ifndef MENU_FINAL_H_
#define MENU_FINAL_H_
#include "../lib/menu_final.h"
#endif

#include "../lib/pingouin.h"

int dep_ennemy(int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy, personnage_t *ennemy);
int dep(int en_mvmt, int sauter, int attaquer, int frame, pingouin_t *player);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Event event;

SDL_Texture *bgTexture = NULL;
SDL_Texture *solTexture = NULL;
SDL_Texture *textures[3];
SDL_Texture *home_texture = NULL;
SDL_Texture *coups[3];
SDL_Texture *ennemy_texture[2];

SDL_Rect dest_rect = {0, 0, 640, 480};
SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
SDL_Rect solRect = {0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 99};
SDL_Rect playerRect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 50, 60};
SDL_Rect home_rect = {10, 10, 50, 50};
SDL_Rect ennemy_rect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 50, 60};

int frame = 0;
int type_coups = 0;
int type_coups_ennemy = 0;
int xVel = 0;
int yVel = 0;
int check_saut = FALSE;
int animationDelay = 0;
int counter = 0;
int ennemy_apparait = FALSE;

/**
 * \file menu.c
 * \brief Fichier pour le menu du jeu et ouvre ou quitte le jeu
 * \author Chevallier Hugo
 * \version 2
 * \date 03/03/2023
 */

/**
 * \fn int init_win()
 * \brief Fonction pour initialiser la fenêtre et le renderer (rendu)
 */
int init_win()
{
    window = SDL_CreateWindow("Nouvelle fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return FALSE;
    }
    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return FALSE;
    }
    return TRUE;
}

/**
 * \fn int init_events()
 * \brief Fonction pour initialiser les textures (celles utiles pour jouer) à partir de surfaces
 */
int init_events()
{
    if (renderer != NULL)
    {
        SDL_Surface *surfaces[4];
        surfaces[0] = IMG_Load("../IMG/dep1.png");
        surfaces[1] = IMG_Load("../IMG/dep2.png");
        surfaces[2] = IMG_Load("../IMG/dep3.png");
        SDL_Surface *coups_surf[4];
        coups_surf[0] = IMG_Load("../IMG/coups1.png");
        coups_surf[1] = IMG_Load("../IMG/coups2.png");
        coups_surf[2] = IMG_Load("../IMG/coups3.png");
        int i;
        for (i = 0; i < 3; i++)
        {
            if (surfaces[i] == NULL)
            {
                printf("Erreur lors du chargement de la surface : %s\n", SDL_GetError());
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return FALSE;
            }
            textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
            SDL_FreeSurface(surfaces[i]);
            if (textures[i] == NULL)
            {
                printf("Erreur lors du chargement de la texture : %s\n", SDL_GetError());
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return FALSE;
            }

            if (coups_surf[i] == NULL)
            {
                printf("Erreur lors du chargement de la surface : %s\n", SDL_GetError());
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return FALSE;
            }
            coups[i] = SDL_CreateTextureFromSurface(renderer, coups_surf[i]);
            SDL_FreeSurface(coups_surf[i]);
            if (coups[i] == NULL)
            {
                printf("Erreur lors du chargement de la texture : %s\n", SDL_GetError());
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return FALSE;
            }
        }
        SDL_Surface *home_surface = IMG_Load("../IMG/home.png");
        if (home_surface == NULL)
        {
            printf("Erreur lors du chargement de la surface : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            return FALSE;
        }
        home_texture = SDL_CreateTextureFromSurface(renderer, home_surface);
        SDL_FreeSurface(home_surface);
        if (home_texture == NULL)
        {
            printf("Erreur de création des textures : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * \fn int init_bg_jeu_windows()
 * \brief Fonction pour initialiser l'arrière plan et le sol pour le jeux
 */
int init_bg_jeu_windows()
{
    if (renderer != NULL)
    {
        SDL_Surface *sol = IMG_Load("../IMG/sol.jpg");
        SDL_Surface *bgSurface = IMG_Load("../IMG/fond_map.jpg");
        if (bgSurface == NULL || sol == NULL)
        {
            printf("Background image could not be loaded! SDL_Error: %s\n", SDL_GetError());
            return FALSE;
        }
        solTexture = SDL_CreateTextureFromSurface(renderer, sol);
        SDL_FreeSurface(sol);
        bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
        if (bgTexture == NULL || solTexture == NULL)
        {
            printf("Erreur de création des textures : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * \fn int init_ennemy()
 * \brief Fonction pour initialiser les textures liées à l'ennemi
 */
int init_ennemy()
{
    if (renderer != NULL)
    {
        SDL_Surface *ennemy_surface[2];
        int i;
        for (i = 0; i < 2; i++)
        {
            if (i == 0)
                ennemy_surface[i] = IMG_Load("../IMG/chasseur_attaque1.png");
            else if (i == 1)
                ennemy_surface[i] = IMG_Load("../IMG/chasseur_attaque2.png");
            if (ennemy_surface[i] == NULL)
            {
                printf("Erreur lors du chargement de la surface : %s\n", SDL_GetError());
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return FALSE;
            }
            ennemy_texture[i] = SDL_CreateTextureFromSurface(renderer, ennemy_surface[i]);
            if (ennemy_texture[i] == NULL)
            {
                printf("Erreur lors du chargement de la texture : %s\n", SDL_GetError());
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return FALSE;
            }
            SDL_FreeSurface(ennemy_surface[i]);
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * \fn int menu_principal()
 * \brief Fonction qui créer un menu avec 2 boutons : Play et Exit et créer les textures pour cette interface
 * \return EXIT_SUCCESS ou EXIT_FAILURE : dis si cela à marcher
 */
int menu_principal()
{
    // Création de la fenêtre

    init_win();

    // Chargement de l'image de fond
    SDL_Surface *img_fond = IMG_Load("../IMG/iceberg.png");
    if (img_fond == NULL)
    {
        printf("Erreur de chargement de l'image de fond : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }
    SDL_Texture *fond_texture = SDL_CreateTextureFromSurface(renderer, img_fond);
    SDL_FreeSurface(img_fond);
    if (fond_texture == NULL)
    {
        printf("Erreur de création des textures : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }

    // Chargement de la texture du bouton "Play"
    SDL_Surface *jouer_surface = IMG_Load("../IMG/play.png");
    if (jouer_surface == NULL)
    {
        printf("Erreur de chargement de l'image du bouton 'Jouer' : %s\n", SDL_GetError());
        SDL_FreeSurface(img_fond);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }
    SDL_Texture *jouer_texture = SDL_CreateTextureFromSurface(renderer, jouer_surface);
    SDL_FreeSurface(jouer_surface);
    if (jouer_texture == NULL)
    {
        printf("Erreur de création des textures : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }
    // Chargement de la texture du bouton "Quitter"
    SDL_Surface *quitter_surface = IMG_Load("../IMG/exit.png");
    if (quitter_surface == NULL)
    {
        printf("Erreur de chargement de l'image du bouton 'Quitter' : %s\n", SDL_GetError());
        SDL_FreeSurface(img_fond);
        SDL_FreeSurface(jouer_surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }
    SDL_Texture *quitter_texture = SDL_CreateTextureFromSurface(renderer, quitter_surface);
    SDL_FreeSurface(quitter_surface);
    if (quitter_texture == NULL)
    {
        printf("Erreur de création des textures : %s\n", SDL_GetError());
        SDL_DestroyTexture(jouer_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }

    // Positionnement des boutons
    SDL_Rect jouer_rect = {240, 200, 160, 60};
    SDL_Rect quitter_rect = {240, 300, 160, 60};

    // Boucle d'evenments
    int quit = FALSE;
    while (quit == FALSE)
    {
        // SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT: // si on clique sur la croix pour fermer la fenetre
                quit = TRUE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // si l'utilisateur a cliqué sur le bouton gauche de la souris
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    // bouton jouer
                    if (x >= jouer_rect.x && x < jouer_rect.x + jouer_rect.w && y >= jouer_rect.y && y < jouer_rect.y + jouer_rect.h)
                    {
                        // Le bouton "Jouer" a été cliqué
                        printf("Bouton 'Jouer' cliqué\n");
                        // Fermeture de la fenêtre du menu principal
                        SDL_DestroyTexture(jouer_texture);
                        SDL_DestroyTexture(quitter_texture);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        // Affichage de la fenêtre du jeu
                        jeu_window();
                        // Affichage du menu principal
                        menu_principal();
                        quit = TRUE;
                    }
                    // bouton quitter
                    else if (x >= quitter_rect.x && x < quitter_rect.x + quitter_rect.w && y >= quitter_rect.y && y < quitter_rect.y + quitter_rect.h)
                    {
                        // Le bouton "Quitter" a été cliqué
                        printf("Bouton 'quitter' cliqué\n");
                        // Fermeture de la fenêtre du menu principal
                        SDL_DestroyTexture(jouer_texture);
                        SDL_DestroyTexture(quitter_texture);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        // Fermeture du jeu

                        SDL_Quit();
                        quit = TRUE;
                    }
                }
                break;
            }
        }
        // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Affichage de l'image de fond
        SDL_RenderCopy(renderer, fond_texture, NULL, NULL);
        // Affichage des boutons
        SDL_RenderCopy(renderer, jouer_texture, NULL, &jouer_rect);
        SDL_RenderCopy(renderer, quitter_texture, NULL, &quitter_rect);

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);
    }
    // Libération des ressources
    SDL_DestroyTexture(jouer_texture);
    SDL_DestroyTexture(quitter_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;
}

/**
 * \fn int jeu_windows()
 * \brief Fonction qui créer une fenêtre pour jouer au jeu
 * \return EXIT_SUCCESS ou EXIT_FAILURE : dit si cela à marcher
 */
int jeu_window()
{
    // Chargement des images à afficher en boucle
    personnage_t *ennemy = malloc(sizeof(personnage_t));
    int check_win = init_win();
    int check_bg = init_bg_jeu_windows();
    int check_adv = init_ennemy();
    int en_mvmt = FALSE; // permet de savoir si le pingouin est en mouvement
    int sauter = FALSE;
    int attaquer = FALSE;
    int quit = FALSE;
    int avancer_ennemy = FALSE; // permet de savoir si le pingouin est en mouvement
    int reculer_ennemy = FALSE;
    int sauter_ennemy = FALSE;
    int attaque_ennemy = FALSE;
    charger_base(ennemy, "../src/stat/chasseur.txt");
    if (check_win && check_bg && check_adv)
    {
        while (quit == FALSE)
        {
            if (events_dep(en_mvmt, sauter, attaquer))
            {/*
                ennemy_apparait = TRUE;
                if (ennemy_apparait == TRUE)
                {
                    if (choixdep_ennemy(&avancer_ennemy, &sauter_ennemy, &attaque_ennemy, &reculer_ennemy))
                    {

                        dep_ennemy(&avancer_ennemy, &sauter_ennemy, &attaque_ennemy, &reculer_ennemy, ennemy);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                        SDL_RenderClear(renderer);
                        if (playerRect.x + playerRect.w == ennemy_rect.x + ennemy_rect.w)
                        {
                            ennemy_rect.x += 10;
                            printf("toucher\n");
                        }
                    }
                }*/
            }
        }
        // Fermeture de la nouvelle fenetre et libération des ressources

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyTexture(solTexture);
        SDL_DestroyTexture(home_texture);

        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int events_dep(int en_mvmt, int sauter, int attaquer)
{
    int frame = 2;
    pingouin_t *player = malloc(sizeof(pingouin_t));
    int nbItemG = 3;
    item_t *listeItemG[nbItemG];

    item_t *epee = malloc(sizeof(item_t));
    item_t *chaussures = malloc(sizeof(item_t));
    item_t *bouclier = malloc(sizeof(item_t));
    charger_item(epee, "../src/stat/epee.txt");
    charger_item(chaussures, "../src/stat/chaussures.txt");
    charger_item(bouclier, "../src/stat/bouclier.txt");
    listeItemG[0] = epee;
    listeItemG[1] = chaussures;
    listeItemG[2] = bouclier;
    charger_ping(player, "../src/stat/pingouin.txt", "GMK", listeItemG, 3);

    if (init_events())
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                break;
            case SDL_MOUSEBUTTONDOWN:
                // si l'utilisateur a cliqué sur le bouton gauche de la souris
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    if (x >= home_rect.x && x <= home_rect.x + home_rect.w && y >= home_rect.y && y <= home_rect.y + home_rect.h)
                    {
                        // Le bouton "Quitter" a été cliqué
                        printf("Bouton 'home' cliqué\n");
                        // Fermeture de la fenetre du jeu
                        SDL_DestroyTexture(solTexture);
                        SDL_DestroyTexture(bgTexture);
                        SDL_DestroyTexture(home_texture);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        //  Affichage du menu principal
                        menu_principal();
                    }
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    xVel = -5;
                    en_mvmt = TRUE;
                    break;
                case SDLK_d:
                    xVel = 5;
                    en_mvmt = TRUE;
                    break;
                case SDLK_p:
                    attaquer = TRUE;
                    break;
                case SDLK_SPACE:
                    if (!sauter)
                    {
                        sauter = TRUE;
                        yVel = -10;
                        SDL_DestroyTexture(textures[frame]);
                        frame = 0;
                    }
                    break;
                case SDLK_DOWN:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    xVel = 0;
                    en_mvmt = FALSE;
                    break;
                case SDLK_d:
                    xVel = 0;
                    en_mvmt = FALSE;
                    break;
                case SDLK_p:
                    attaquer = FALSE;
                    break;
                case SDLK_SPACE:
                    sauter = FALSE;
                }
                break;
            }
        }
    }
    dep(en_mvmt, sauter, attaquer, frame, player);
    return (TRUE);
}

void affiche_rendu_saut()
{
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    SDL_RenderCopy(renderer, solTexture, NULL, &solRect);
    SDL_RenderCopy(renderer, home_texture, NULL, &home_rect);
    SDL_RenderCopy(renderer, textures[2], NULL, &playerRect);
    SDL_RenderCopy(renderer, coups[type_coups], NULL, &playerRect);

    SDL_RenderPresent(renderer);
    if (check_saut == TRUE)
        SDL_Delay(30);
    SDL_RenderClear(renderer);
}

int dep(int en_mvmt, int sauter, int attaquer, int frame, pingouin_t *player)
{
    if (sauter)
        check_saut = TRUE;
    if (en_mvmt)
    {
        counter++;
        if (counter >= animationDelay)
        {
            frame++;
            if (frame >= 2)
                frame = 0;
            counter = 0;
        }
        if (sauter)
        {
            while (playerRect.y >= (PINGOUIN_Y_SAUT))
            {
                playerRect.y -= 5;
                player->pers->coord.y = playerRect.y;
                playerRect.x += xVel;
                player->pers->coord.x = playerRect.x;
                if (playerRect.x < 0)
                {
                    playerRect.x = SCREEN_WIDTH + playerRect.w;
                    player->pers->coord.x = playerRect.x;
                }
                else if (playerRect.x > SCREEN_WIDTH - playerRect.w)
                {
                    playerRect.x = SCREEN_WIDTH - playerRect.w;
                    player->pers->coord.x = playerRect.x;
                }
                if (ennemy_apparait == FALSE)
                    affiche_rendu_saut();
                else
                    affiche_rendu();
            }
            while (playerRect.y <= (POS_PING_SOL))
            {
                playerRect.y += 5;
                player->pers->coord.y = playerRect.y;
                if (ennemy_apparait == FALSE)
                    affiche_rendu_saut();
                else
                    affiche_rendu();
            }
            check_saut = FALSE;
            sauter = FALSE;
        }
        else
        {
            playerRect.x += xVel;
            player->pers->coord.x = playerRect.x;
            if (playerRect.x < 0)
            {
                playerRect.x = SCREEN_WIDTH + playerRect.w;
                player->pers->coord.x = playerRect.x;
            }
            else if (playerRect.x > SCREEN_WIDTH - playerRect.w)
            {
                playerRect.x = SCREEN_WIDTH - playerRect.w;
                player->pers->coord.x = playerRect.x;
            }
            if (en_mvmt)
            {
                SDL_DestroyTexture(textures[frame]);
                frame++;
                if (frame >= 2)
                {
                    frame = 0;
                }
                textures[frame] = IMG_LoadTexture(renderer, "../IMG/dep2.png");
            }
            else
            {
                SDL_DestroyTexture(textures[frame]);
                textures[frame] = IMG_LoadTexture(renderer, "../IMG/dep1.png");
            }
        }
    }
    if (sauter)
    {
        while (playerRect.y >= (PINGOUIN_Y_SAUT))
        {
            playerRect.y -= 5;
            player->pers->coord.y = playerRect.y;
            if (ennemy_apparait == FALSE)
                affiche_rendu_saut();
            else
                affiche_rendu();
        }
        while (playerRect.y <= (POS_PING_SOL))
        {
            playerRect.y += 5;
            player->pers->coord.y = playerRect.y;
            if (ennemy_apparait == FALSE)
                affiche_rendu_saut();
            else
                affiche_rendu();
        }
        check_saut = FALSE;
        sauter = FALSE;
    }
    if (attaquer)
    {
        playerRect.w = 60;
        type_coups = 2;
        attaquer = FALSE;
    }
    else
    {
        playerRect.h = 60;
        playerRect.w = 50;
        type_coups = 0;
    }
   // SDL_RenderClear(renderer);
    if (ennemy_apparait == FALSE)
    {
        affiche_rendu_saut();
        // SDL_RenderClear(renderer);
    }
    else
        affiche_rendu();

    return (TRUE);
}

int choixdep_ennemy(int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy)
{
    int attack_type = rand() % 10;
    switch (attack_type)
    {
    case 0:
        *avancer_ennemy = TRUE;
        *sauter_ennemy = FALSE;
        *attaque_ennemy = FALSE;
        *reculer_ennemy = FALSE;
        break;
    case 1:
        *avancer_ennemy = TRUE;
        *sauter_ennemy = FALSE;
        *attaque_ennemy = FALSE;
        *reculer_ennemy = FALSE;
        break;
    case 2:
        *avancer_ennemy = FALSE;
        *sauter_ennemy = FALSE;
        *attaque_ennemy = TRUE;
        *reculer_ennemy = FALSE;
        break;
    case 3:
        *avancer_ennemy = FALSE;
        *sauter_ennemy = FALSE;
        *attaque_ennemy = FALSE;
        *reculer_ennemy = TRUE;
        break;
    case 4:
        *avancer_ennemy = TRUE;
        *sauter_ennemy = TRUE;
        *attaque_ennemy = FALSE;
        *reculer_ennemy = FALSE;
        break;
    case 5:
        *avancer_ennemy = FALSE;
        *sauter_ennemy = TRUE;
        *attaque_ennemy = FALSE;
        *reculer_ennemy = TRUE;
        break;
    default:
        *avancer_ennemy = FALSE;
        *sauter_ennemy = FALSE;
        *attaque_ennemy = FALSE;
        *reculer_ennemy = FALSE;
        break;
    }
    return TRUE;
}

void affiche_rendu()
{
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    SDL_RenderCopy(renderer, solTexture, NULL, &solRect);
    SDL_RenderCopy(renderer, home_texture, NULL, &home_rect);
    SDL_RenderCopy(renderer, textures[2], NULL, &playerRect);
    SDL_RenderCopy(renderer, ennemy_texture[type_coups_ennemy], NULL, &ennemy_rect);
    SDL_RenderCopy(renderer, coups[type_coups], NULL, &playerRect);

    
}

int dep_ennemy(int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy, personnage_t *ennemy)
{
    if (*reculer_ennemy)
        xVel = -xVel;
    counter++;
    if (counter >= animationDelay)
    {
        counter = 0;
    }
    if (*sauter_ennemy)
    {
        while (ennemy_rect.y >= (PINGOUIN_Y_SAUT))
        {
            ennemy_rect.y -= 5;
            ennemy_rect.x -= xVel;
            ennemy->coord.y = ennemy_rect.y;
            ennemy->coord.x = ennemy_rect.x;
            if (ennemy_rect.x < 0)
            {
                ennemy_rect.x = SCREEN_WIDTH + ennemy_rect.w;
                ennemy->coord.x = ennemy_rect.x;
            }
            else if (ennemy_rect.x > SCREEN_WIDTH - ennemy_rect.w)
            {
                ennemy_rect.x = SCREEN_WIDTH - ennemy_rect.w;
                ennemy->coord.x = ennemy_rect.x;
            }
            affiche_rendu();
           // SDL_RenderPresent(renderer);
    //SDL_Delay(30);
    //SDL_RenderClear(renderer);
        }
        while (ennemy_rect.y <= (POS_PING_SOL))
        {
            ennemy_rect.y += 5;
            ennemy->coord.y = ennemy_rect.y;
            affiche_rendu();
        }
        *sauter_ennemy = FALSE;
    }
    else
    {
        int n = 10;
        while (n != 0)
        {
            ennemy_rect.x += xVel - 1;
            ennemy->coord.x = ennemy_rect.x;
            if (ennemy_rect.x < 0)
            {
                ennemy_rect.x = SCREEN_WIDTH + ennemy_rect.w;
                ennemy->coord.x = ennemy_rect.x;
            }
            else if (ennemy_rect.x > SCREEN_WIDTH - ennemy_rect.w)
            {
                ennemy_rect.x = SCREEN_WIDTH - ennemy_rect.w;
                ennemy->coord.x = ennemy_rect.x;
            }
            n--;
            affiche_rendu();
          //  SDL_RenderPresent(renderer);
    //SDL_Delay(30);
    //SDL_RenderClear(renderer);
        }
        // n = 10;
    }
    if (*attaque_ennemy)
    {
        ennemy_rect.w = 60;
        type_coups_ennemy = 1;
        *attaque_ennemy = FALSE;
    }
    else
    {
        ennemy_rect.h = 60;
        ennemy_rect.w = 50;
        type_coups_ennemy = 0;
    }
    // SDL_RenderClear(renderer);
    affiche_rendu();
    SDL_RenderPresent(renderer);
   // SDL_Delay(30);
   // SDL_RenderClear(renderer);
    //SDL_RenderClear(renderer);
    /*
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    SDL_RenderCopy(renderer, ennemy_texture[type_coups], NULL, &ennemy_rect);
//SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    SDL_RenderCopy(renderer, solTexture, NULL, &solRect);
    SDL_RenderPresent(renderer);
*/
    return (TRUE);
}

int main()
{
    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur lors de l'initialisation de SDL2 : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Affichage du menu principal
    menu_principal();
    // Fermeture de SDL2
    int i;
    for (i = 0; i < 3; i++)
    {
        if (i < 2)
            SDL_DestroyTexture(ennemy_texture[i]);
        SDL_DestroyTexture(textures[i]);
        SDL_DestroyTexture(coups[i]);
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
