#ifndef __DEPLACEMENT_H_
#define __DEPLACEMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "grille.h"
#include "personnage.h"

/**Fonction qui renvoie l'id de la case ou le personnage est sensé se déplacer*/
int getDepGrille (perso p, grille g, int direction);
/**Fonction qui déplace les coordonnées du personnage s'il n'y a pas de collisions*/
void getDeplacementPerso (perso p, int type, grille g, int direction);
/**Fonction qui déplace les coordonnées du personnage*/
void DeplacementPerso (perso p, int direction);


#endif