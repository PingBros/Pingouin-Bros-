#include "../lib/pingouin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern void calcul_degats(personnage_t *p1, personnage_t *p2){
    p2->vie -= p1->degats * (1 - (p2->defense / 100));
}

extern int vivant(personnage_t * pers){
    return pers->vie > 0;
}

extern int convertion_saut(personnage_t * pers){
    return (pers->saut * 10);
}

extern int convertion_vitesse_a(personnage_t * pers){
    return (pers->vitesse_a); // A compléter
}

extern int convertion_vitesse_d(personnage_t * pers){
    return (pers->vitesse_d); // A compléter
}

extern int Init_Jeu(char * Pseudo){
    return 1;
}

extern void Detruire_Jeu(){

}
