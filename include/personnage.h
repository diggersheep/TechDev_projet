/**
* @file personnage.h
* @brief proto personnage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#ifndef __PERSONNAGE_H_
#define __PERSONNAGE_H_


#include <SDL/SDL.h>


#include "objet.h"

#define VARCHAR 256	

/**structure d'une position*/
typedef struct
{
	int x;
	int y;
} Pos;


/**structure d'un personnage*/
typedef struct
{
	char* nom;
	Pos   pos;
	int   pv;
	int   pv_max;
	int   atk;
	int   def;
	int  orientation;
	Objet equip[5];
	SDL_Surface* img[4];

} Perso;
typedef Perso* perso;


/**Lis la position d'un personnage par rapport a un fichier*/
Pos getPos (char *path);
/**Défini une nouvelle position*/
Pos newPos (int x, int y);
/**Créé un nouveau personnage*/
perso setPerso (int pv, int atk, int def, short orientation, char* up, char* rigth, char* down, char* left);
/**Désalloue un personnage*/
void setPersoPos (perso p, Pos coord);


#endif