#ifndef __MONSTRE_h_
#define __MONSTRE_h_

/**
* @file monstre.h
* @brief proto monstre
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 04-05-2015
*/

#include "grille.h"
#include "objet.h"
#include "personnage.h"

#define MAX_MOB 1000
#define MAX_MOB_SCREEN 100
/**Type monstre*/
typedef perso mob;
typedef struct
{
	mob m;
	int id;
	unsigned short move;//0->static, 1->rand, 2->agro
}Mob_elem;

Mob_elem array_mob[MAX_MOB];
int      array_mob_length;

Mob_elem array_mob_screen[MAX_MOB_SCREEN];
int      array_mob_screen_length;

/***/
Mob_elem setMob (int pv, int atk, int def, short orientation, char* up, char* rigth, char* down, char* left, int id, unsigned short move);
/**Alloue tous les mobs possibles d'avoir dans le jeu*/
void setAllMob (void);
/**Désalloue un monstre (même fonction que pour un personnage)*/
void unsetMob (mob m);
/**Désalloue tout les mobs chargés (sauf ceux a l'écran, mais normalement, il n'y en a plus)*/
void unsetAllMob (void);

/**Mob affichés*/
void initMob (grille g, int id_remplacement);

/**proxénète pour mob ^^ */
int rechercheMob (int id);

/**tue un monstre ...  Bob est gentil, mais on le tue quand même :(*/
void killBob(mob m, int i);

#endif