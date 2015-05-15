#ifndef __CONTROLE_H_
#define __CONTROLE_H_

#include "grille.h"
#include "personnage.h"

SDL_Event screen_event;
int game_state;

/**Fonction qui renvoie un int si une touche est pressé*/
int pause_touche (perso p, grille g);

#endif