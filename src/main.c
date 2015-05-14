/**
* @file main.c
* @brief main
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "personnage.h"
#include "grille.h"
#include "controle.h"
#include "objet.h"
#include "SDL_affichage.h"
#include "gestion.h"
#include "deplacement.h"
#include "monstre.h"



int main(int argc, char *argv[])
{
	//initialisation du temps
	srand(  time(NULL) );

	//initialisation de la grille et du joueur
	grille g = NULL;
	perso p = NULL;

	//boucle de jeu
	jeu(p, g, argv[1]);
	
	//fin
	return 0;
}