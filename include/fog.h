/**
* @file fog.h
* @brief proto visibilité
* @author Alexandre COMBEAU, Alain KABBOUh
* @date 14-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

#include "personnage.h"
#include "grille.h"

grille grid_fog;
SDL_Surface* noir;

void initFogGrid (grille g);

void FreeFogGrid (void);


void unfogPerso (perso p);

void afficherGrilleFog (void);

void unfogGrid (perso p, grille g, int dist);