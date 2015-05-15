#ifndef __JEU_H_
#define __JEU_H_

/**
* @file jeu.h
* @brief jeu
* @author Alexandre COMBEAU
* @date 04-05-2015
*/

#include "personnage.h"
#include "grille.h"
#include "objet.h"

/**Boocle de jeu, a peu près tout ce qu'il y aura dans le main en fait*/
void jeu (perso p, grille g, char* path, int fog_activation);

#endif