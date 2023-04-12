#ifndef MENU_FINAL_H_
#define MENU_FINAL_H_
#include "../lib/interface_graphique.h"
#endif

#include "../lib/pingouin.h"

int choixdep_ennemy(int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy);
int dep_ennemy(map_t *map, int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy, personnage_t *ennemy);

/**
 * \file interface_graphique.c
 * \brief Fichier pour l'interface graphique où on utilise également les fonctions du moteur de jeu
 * \author Patault Kylian et Chevallier Hugo
 * \version 3
 * \date 9 Avril 2023
 *
 */
SDL_Renderer *renderer = NULL;

SDL_Texture *textures[3];
SDL_Texture *coups[3];
SDL_Texture *ennemy_texture[2];
SDL_Texture *tileset = NULL;
SDL_Texture *home_texture = NULL;
SDL_Event event;
SDL_Rect playerRect = {600, 357, 50, 60};
SDL_Rect ennemy_rect = {850, 357, 50, 60};
int check_attack_ennemy = 0;

int deb = 0;
int fin = 50;
int xVel = 0;
int attack = FALSE, saut = FALSE;
int check_saut = FALSE;
int tile_size = LARGEUR_TILE * HAUTEUR_TILE;

pingouin_t *player = NULL;
personnage_t *ennemy = NULL;
/**
 * \fn void charger_map(map_t *carte, char *chemin)
 * \brief Fonction de chargement pour la map
 * \param carte Carte de type map_t
 * \param chemin Chemin pour accéder au fichier .txt pour générer la carte
 */
void charger_map(map_t *carte, char *chemin)
{
    FILE *f = fopen(chemin, "r");

    int largeur;
    int hauteur;
    char c;
    char chaine[MAXCAR_MAP];
    int i; //, j;
    if (f != NULL)
    {
        fscanf(f, "level:%i %i\n", &largeur, &hauteur);
        carte->largeur = largeur;
        carte->hauteur = hauteur;
        fscanf(f, "%c", &c);
        // char *tab[hauteur];
        if (c == 'd' && !feof(f))
        {
            for (i = 0; !(feof(f)) && (i < carte->hauteur + 1); i++)
            {
                fscanf(f, "%s\n", chaine);
                carte->table[i] = malloc(strlen(chaine) * sizeof(char) * +1);
                strcpy(carte->table[i], chaine);
            }
        }
    }
    fclose(f);
}

/**
 * \fn void seconde_map(map_t *map, int deb, int fin, char *s_map[])
 * \brief Fonction qui créer un plus petit tableau pour la map dans la fonction afficher
 * \param map map de type map_t
 * \param s_map tableau pour afficher la map
 */
void seconde_map(map_t *map, char *s_map[])
{
    int i, j;
    int x, y = 0;
    char chaine[MAXCAR_MAP];

    for (i = 0; i < map->hauteur; i++)
    {
        x = 0;
        for (j = playerRect.x - 600; j < playerRect.x - 550; j++)
        {
            chaine[x] = map->table[i][j];
            x++;
        }
        chaine[x] = '\0';
        s_map[y] = malloc(strlen(chaine) * sizeof(char) * +1);
        strcpy(s_map[y], chaine);
        y++;
    }
}

/**
 * \fn void charger_map(map_t *carte, char *chemin)
 * \brief Fonction de chargement pour la map
 * \param renderer rendu du jeu pour afficher tous les éléments
 * \param tileset texture qui permet d'afficher la map en fonction de la map
 * \param map map de type map_t
 * \param perso texture permettant de représenter le personnage (ici un pingouin)
 * \param home_texture texture du bouton Home pour l'afficher sur la fenêtre
 * \param deb indice de début pour avancer au fur et à mesure
 * \param fin indice de fin pour avancer, donc on affiche la map de 50 en 50
 */
void Afficher(SDL_Renderer *renderer, SDL_Texture *tileset, map_t *map, SDL_Texture *perso, SDL_Texture *home_texture, int deb, int fin)
{
    int i, j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    SDL_Rect home_rect = {10, 10, 50, 50};
    Rect_source.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    Rect_dest.w = LARGEUR_TILE;
    Rect_dest.h = HAUTEUR_TILE;
    char *s_map[MAXCAR_MAP];
    seconde_map(map, s_map);
    for (i = 0; i < END; i++)
    {
        for (j = 0; j < map->hauteur; j++)
        {
            Rect_dest.x = i * LARGEUR_TILE;
            Rect_dest.y = j * HAUTEUR_TILE;
            Rect_source.x = (s_map[j][i] - '0') * LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_RenderCopy(renderer, tileset, &Rect_source, &Rect_dest);
            if (s_map[j][i] == '8')
            {
                if (check_attack_ennemy)
                    SDL_RenderCopy(renderer, ennemy_texture[1], NULL, &ennemy_rect);
                else
                    SDL_RenderCopy(renderer, ennemy_texture[0], NULL, &ennemy_rect);
            }

            if (attack == TRUE)
            {
                SDL_RenderCopy(renderer, coups[2], NULL, &playerRect);
            }
            else
                SDL_RenderCopy(renderer, perso, NULL, &playerRect);
            SDL_RenderCopy(renderer, home_texture, NULL, &home_rect);
        }
    }
    SDL_RenderPresent(renderer);
    if (check_saut == TRUE)
        SDL_Delay(30);
    SDL_RenderClear(renderer);
}

/**
 * \fn int menu_principal(map)
 * \brief Fonction qui créer un menu avec 2 boutons : Play et Exit et créer les textures pour cette interface
 * \return EXIT_SUCCESS ou EXIT_FAILURE : dit si cela à marcher, retourne TRUE si on choisit de jouer au jeu et FALSE si un des éléments c'est mal charger ou si on a appuyer sur "Quitter"
 */
int menu_principal()
{
    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Pingouin Bros - Menu", 0, 0, 640, 480, SDL_SWSURFACE);
    if (window == NULL)
    {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return FALSE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return FALSE;
    }

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

    SDL_Surface *commande_surf = IMG_Load("../IMG/commandes.png");
    if (quitter_surface == NULL)
    {
        printf("Erreur de chargement de l'image du bouton 'Quitter' : %s\n", SDL_GetError());
        SDL_FreeSurface(img_fond);
        SDL_FreeSurface(commande_surf);
        SDL_DestroyTexture(jouer_texture);
        SDL_DestroyTexture(quitter_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }
    SDL_Texture *commandes = SDL_CreateTextureFromSurface(renderer, commande_surf);
    if (quitter_texture == NULL)
    {
        printf("Erreur de création des textures : %s\n", SDL_GetError());
        SDL_DestroyTexture(jouer_texture);
        SDL_DestroyTexture(quitter_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return FALSE;
    }
    SDL_FreeSurface(commande_surf);
    // Positionnement des boutons
    SDL_Rect jouer_rect = {240, 200, 160, 60};
    SDL_Rect quitter_rect = {240, 300, 160, 60};
    SDL_Rect cmd_rect = {250, -25, 550, 400};
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
                        quit = TRUE;
                        // génération et affichage de la carte du jeu et du jeu dans sa globalité

                        jeu();
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
                        return FALSE;
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
        SDL_RenderCopy(renderer, commandes, NULL, &cmd_rect);

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);
    }
    return EXIT_SUCCESS;
}

/**
 * \fn int jeu()
 * \brief Fonction génère la map du jeu et permet de jouer
 * \return Si on a cliqué sur le bouton "Home" pour revenir au menu, et FALSE si un des éléments c'est mal chargé
 */
int jeu()
{
    player = malloc(sizeof(pingouin_t));
    int nbItemG = 3;
    item_t *listeItemG[nbItemG];

    item_t *epee = malloc(sizeof(item_t));
    item_t *chaussures = malloc(sizeof(item_t));
    item_t *bouclier = malloc(sizeof(item_t));
    charger_item(epee, "../src/fich_txt/epee.txt");
    charger_item(chaussures, "../src/fich_txt/chaussures.txt");
    charger_item(bouclier, "../src/fich_txt/bouclier.txt");
    listeItemG[0] = epee;
    listeItemG[1] = chaussures;
    listeItemG[2] = bouclier;
    charger_ping(player, "../src/fich_txt/pingouin.txt", "GMK", listeItemG, 3);

    SDL_Window *screen;

    SDL_Surface *bgSurface = NULL;

    map_t *map = malloc(sizeof(map_t));
    charger_map(map, "../src/fich_txt/map.txt");

    screen = SDL_CreateWindow("Pingouin Bros - Jeu", 0, 0, LARGEUR_TILE * fin, HAUTEUR_TILE * map->hauteur, SDL_SWSURFACE);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    bgSurface = IMG_Load("../IMG/tileset2.png");
    if (bgSurface == NULL)
    {
        printf("Background image could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }
    SDL_Surface *home_surface = IMG_Load("../IMG/home.png");
    if (home_surface == NULL)
    {
        printf("Erreur lors du chargement de la surface : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(screen);
        return FALSE;
    }
    home_texture = SDL_CreateTextureFromSurface(renderer, home_surface);
    SDL_FreeSurface(home_surface);
    if (home_texture == NULL)
    {
        printf("Erreur de création des textures : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(screen);
        SDL_Quit();
        return FALSE;
    }

    tileset = SDL_CreateTextureFromSurface(renderer, bgSurface);
    if (tileset == NULL)
    {
        printf("Echec de chargement tileset2.png\n");
        SDL_Quit();
        system("pause");
        exit(-1);
    }

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
            SDL_DestroyWindow(screen);
            return FALSE;
        }
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
        SDL_FreeSurface(surfaces[i]);
        if (textures[i] == NULL)
        {
            printf("Erreur lors du chargement de la texture : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(screen);
            return FALSE;
        }

        if (coups_surf[i] == NULL)
        {
            printf("Erreur lors du chargement de la surface : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(screen);
            return FALSE;
        }
        coups[i] = SDL_CreateTextureFromSurface(renderer, coups_surf[i]);
        SDL_FreeSurface(coups_surf[i]);
        if (coups[i] == NULL)
        {
            printf("Erreur lors du chargement de la texture : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(screen);
            return FALSE;
        }
    }
    SDL_Surface *ennemy_surface[2];
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
            SDL_DestroyWindow(screen);
            return FALSE;
        }
        ennemy_texture[i] = SDL_CreateTextureFromSurface(renderer, ennemy_surface[i]);
        if (ennemy_texture[i] == NULL)
        {
            printf("Erreur lors du chargement de la texture : %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(screen);
            return FALSE;
        }
        SDL_FreeSurface(ennemy_surface[i]);
    }
    SDL_Rect home_rect = {10, 10, 50, 50};
    int quit = 0;
    int avancer = FALSE;
    int reculer = FALSE;
    int sauter = FALSE;
    int avancer_ennemy = FALSE; // permet de savoir si le pingouin est en mouvement
    int reculer_ennemy = FALSE;
    int sauter_ennemy = FALSE;
    int attaque_ennemy = FALSE;
    ennemy = malloc(sizeof(personnage_t));
    charger_base(ennemy, "../src/stat/chasseur.txt");
    while (fin != map->largeur && !quit)
    {
        Afficher(renderer, tileset, map, textures[2], home_texture, deb, fin);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
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
                        SDL_DestroyTexture(home_texture);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(screen);
                        destruction_pingouin(&player);
                        //  Affichage du menu principal
                        menu_principal();
                        return TRUE;
                    }
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    reculer = TRUE;
                    break;
                case SDLK_d:
                    avancer = TRUE;
                    break;
                case SDLK_p:
                    attack = TRUE;
                    break;
                case SDLK_SPACE:
                    sauter = TRUE;
                    break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    reculer = FALSE;
                    break;
                case SDLK_d:
                    avancer = FALSE;
                    break;
                case SDLK_p:
                    attack = FALSE;
                    break;
                case SDLK_SPACE:
                    sauter = FALSE;
                    break;
                }
                break;
            }
            // collision(map);
        }
        deplacements(map, avancer, reculer, sauter);
        if (choixdep_ennemy(&avancer_ennemy, &sauter_ennemy, &attaque_ennemy, &reculer_ennemy))
            dep_ennemy(map, &avancer_ennemy, &sauter_ennemy, &attaque_ennemy, &reculer_ennemy, ennemy);
        // SDL_Delay(250);
        // SDL_RenderClear(renderer);
        // deb += 1;
        // fin += 1;
    }

    do
    {
        SDL_WaitEvent(&event);
    } while (event.type != SDL_KEYDOWN);

    SDL_DestroyTexture(tileset);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    destruction_pingouin(&player);
    SDL_Quit();
    return EXIT_SUCCESS;
}

/**
 * \fn void deplacements(map_t *map, int avancer, int reculer, int sauter)
 * \brief Fonction qui permet de réaliser les déplacements en fonction de la / des touche(s) que l'on presse
 * \param map map de type map_t
 * \param avancer valeur : TRUE ou FALSE si on avance ou pas
 * \param reculer valeur : TRUE ou FALSE si on recule ou pas
 * \param sauter valeur : TRUE ou FALSE si on saute ou pas
 */
void deplacements(map_t *map, int avancer, int reculer, int sauter)
{
    int h_saut = 17;
    if (sauter)
        check_saut = TRUE;
    if (reculer)
    {
        if (playerRect.x > 600)
            playerRect.x -= 1;
    }
    if (avancer)
    {
        if (sauter)
        {
            while (h_saut != 0)
            {

                playerRect.y -= 2;
                player->pers->coord.y = playerRect.y;
                playerRect.x += 1;
                player->pers->coord.x = playerRect.x;

                h_saut--;

                Afficher(renderer, tileset, map, textures[1], home_texture, deb, fin);
            }
            while (h_saut != 17 && sauter)
            {

                if (!detect_obstacle(map))
                {
                    playerRect.y += 2;
                    player->pers->coord.y = playerRect.y;
                    h_saut++;
                }
                else
                    sauter = FALSE;

                Afficher(renderer, tileset, map, textures[1], home_texture, deb, fin);
            }
            sauter = FALSE;
        }
        else
            playerRect.x += 1;
    }
    if (sauter)
    {
        while (h_saut != 0)
        {
            //   if (detect_obstacle(map))
            // printf("%d \n", detect_obstacle(map));

            playerRect.y -= 2;
            player->pers->coord.y = playerRect.y;
            h_saut--;
            Afficher(renderer, tileset, map, textures[1], home_texture, deb, fin);
        }
        while (h_saut != 17 && sauter)
        {
            // printf("%d \n", detect_obstacle(map));
            if (!detect_obstacle(map))
            {
                playerRect.y += 2;
                player->pers->coord.y = playerRect.y;
                h_saut++;
            }
            else
                sauter = FALSE;

            Afficher(renderer, tileset, map, textures[1], home_texture, deb, fin);
        }
        check_saut = FALSE;
        sauter = FALSE;
    }
    if (attack)
    {
        playerRect.w = 55;
        if (detectCollision(playerRect, ennemy_rect))
            calcul_degats(player->pers, ennemy);
    }
    else
        playerRect.w = 50;
    if (!detect_obstacle(map))
    {
        while (!detect_obstacle(map))
        {
            playerRect.y += 2;
            player->pers->coord.y = playerRect.y;
            h_saut++;
        }
    }
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

int dep_ennemy(map_t *map, int *avancer_ennemy, int *sauter_ennemy, int *attaque_ennemy, int *reculer_ennemy, personnage_t *ennemy)
{
    xVel = 3;
    if (*reculer_ennemy)
        xVel = -xVel;
    if (*sauter_ennemy)
    {
        while (ennemy_rect.y >= (320))
        {
            ennemy_rect.y -= 5;
            ennemy_rect.x -= xVel;
            ennemy->coord.y = ennemy_rect.y;
            ennemy->coord.x = ennemy_rect.x;
            if (ennemy_rect.x < 0)
            {
                ennemy_rect.x = map->largeur + ennemy_rect.w;
                ennemy->coord.x = ennemy_rect.x;
            }
            /* else if (ennemy_rect.x > map->largeur - ennemy_rect.w)
             {
                 ennemy_rect.x = map->largeur - ennemy_rect.w;
                 ennemy->coord.x = ennemy_rect.x;
             }*/
            // Afficher(renderer, tileset, map, textures[1], home_texture, deb, fin);
        }
        while (ennemy_rect.y <= (357))
        {
            ennemy_rect.y += 5;
            ennemy->coord.y = ennemy_rect.y;
            //  Afficher(renderer, tileset, map, textures[1], home_texture, deb, fin);
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
                ennemy_rect.x = map->largeur + ennemy_rect.w;
                ennemy->coord.x = ennemy_rect.x;
            } /*
             else if (ennemy_rect.x > map->largeur - ennemy_rect.w)
             {
                 ennemy_rect.x = map->largeur - ennemy_rect.w;
                 ennemy->coord.x = ennemy_rect.x;
             }*/
            n--;
        }
    }
    if (*attaque_ennemy)
    {
        ennemy_rect.w = 60;
        *attaque_ennemy = FALSE;
        check_attack_ennemy = 1;
        if (detectCollision(ennemy_rect, playerRect))
            calcul_degats(ennemy, player->pers);
    }
    else
    {
        ennemy_rect.h = 60;
        ennemy_rect.w = 50;
        check_attack_ennemy = 0;
    }
    return (TRUE);
}

/**
 * \fn int detect_obstacle(map_t *map)
 * \brief Fonction qui détecte les obstacles sur la map
 * \return la valeur
 */
int detect_obstacle(map_t *map)
{
    int tmp = playerRect.x - 600;
    // On calcule l'indice de la case dans laquelle se trouve le personnage
    int row = playerRect.y / HAUTEUR_TILE + 3;
    int col = playerRect.x / LARGEUR_TILE + tmp;

    return (map->table[row][col] != '0');
}

/**
 * \fn int detectCollision(SDL_Rect rect1, SDL_Rect rect2)
 * \brief Fonction qui détecte les collisions entre 2 rectangles
 * \param rect1 rectangle SDL_Rect
 * \param rect2 rectangle SDL_Rect
 * \return 0 si pas de collision, 1 si collision
 */
int detectCollision(SDL_Rect rect1, SDL_Rect rect2)
{
    int left1 = rect1.x;
    int right1 = rect1.x + rect1.w;
    int top1 = rect1.y;
    int bottom1 = rect1.y + rect1.h;

    int left2 = rect2.x;
    int right2 = rect2.x + rect2.w;
    int top2 = rect2.y;
    int bottom2 = rect2.y + rect2.h;

    if (bottom1 <= top2)
    {
        return 0;
    }
    if (top1 >= bottom2)
    {
        return 0;
    }
    if (right1 <= left2)
    {
        return 0;
    }
    if (left1 >= right2)
    {
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO); // prepare SDL
    menu_principal();
    return 0;
}
