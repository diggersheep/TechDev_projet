/**
* @file main.c
* @brief main
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "personnage.h"
#include "grille.h"
#include "controle.h"
#include "objet.h"
#include "SDL_affichage.h"
#include "gestion.h"
#include "deplacement.h"



int main(int argc, char *argv[])
{
	grille g = NULL;
	perso p = NULL;

	jeu(p, g, argv[1]);
	return 0;
}