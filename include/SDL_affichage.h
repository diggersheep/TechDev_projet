/**
* @file SDL_affichage.h
* @brief proto affichage avec SDL
* @author Alexandre COMBEAU
* @date 01-05-2015
*/

#ifndef __SDL_AFFICHAGE_H_
#define __SDL_AFFICHAGE_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "grille.h"

#define MAX_SPRITE 2000

/**Strucure associative : id / image.
	Utile pour gérer efficacement les sprites*/
typedef struct StrObjScreen
{
	int id;
	SDL_Surface* img;
} ObjScreen;

/**Initialise SDL avec une lageur et une hauteur donnée*/
void initSDL (int l, int h);
/**Equivalent de Pause/Wait*/
void attendre_touche (void);
/**Affiche sur la fenetre une image avec par défaut la transpence règlée sur NOIR(0,0,0)*/
void afficher_case (SDL_Surface* img);
/**stock une image*/
void setImage (int id, char* path);
/**Petit écran de chargement :D */
void chargemement (int current, int max);
/**Charge les sprite*/
void setAllImage (void);
/**Désaloue les images stockés dans la variable screen_image*/
void unsetImage (void);
/**Affiche une grille avec SDL*/
void SDL_AfficherGrille(grille g);
#endif