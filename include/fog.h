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

/**creer le brouillard*/
void initFogGrid (grille g);
/**unset le tout*/
void FreeFogGrid (void);

/**peros visible*/
void unfogPerso (perso p);

/***/
void afficherGrilleFog (void);

/**Fonction qui rend visible des parties de la map*/
void unfogGrid (perso p, grille g, int dist);