/**
* @file jeu.c
* @brief jeu
* @author Alexandre COMBEAU
* @date 04-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

#include "personnage.h"
#include "grille.h"
#include "controle.h"
#include "objet.h"
#include "SDL_affichage.h"
#include "gestion.h"
#include "deplacement.h"


void jeu (perso p, grille g, char* path)
{
	g = mopen(path);
	initSDL(sceen_case_size * g->n, sceen_case_size * g->m);

	setAllImage();
	setAllObjet();

	p = setPerso(50, 10, 10, 0, "ressources/img/perso/perso_0.bmp", "ressources/img/perso/perso_1.bmp", "ressources/img/perso/perso_2.bmp", "ressources/img/perso/perso_3.bmp");
	setPersoPos(p, getPos(path));

	

	//fonctions
	SDL_AfficherGrille(g);
	afficherPerso(p);
	afficherStats(p);


	SDL_UpdateRect(screen,0,0,0,0);

	int code = -9999;
	while (code != 0)
	{
		code = pause_touche();
		if (code >= 1  && code <= 4 && game_state)
		{
			screen_position.x = 0;
			screen_position.y = 0;
			GetDeplacementPerso(p, 0, g, code - 1);
		
			SDL_AfficherGrille(g);
			afficherPerso(p);
			gestion (g, p, g->grid[p->pos.y][p->pos.x], 0);
			afficherStats(p);
			SDL_UpdateRect(screen,0,0,0,0);;
		}
		else if (code == -1 && game_state == 1)
		{
			GetDeplacementPerso(p, 0, g, -3);
			SDL_AfficherGrille(g);
			afficherPerso(p);
			gestion (g, p, g->grid[p->pos.y][p->pos.x], 0);
			afficherStats(p);
			SDL_UpdateRect(screen,0,0,0,0);
		}
		else if (code == -1 && game_state == -1)
		{
			afficherPause();
			SDL_UpdateRect(screen,0,0,0,0);;
		}
		else if (code == -2)
		{
			destruction_grille(g);
			unsetPerso(p);
			g = mopen(path);
			p = setPerso(50, 10, 10, 0, "ressources/img/perso/perso_0.bmp", "ressources/img/perso/perso_1.bmp", "ressources/img/perso/perso_2.bmp", "ressources/img/perso/perso_3.bmp");
			setPersoPos(p, getPos(path));
			
			SDL_AfficherGrille(g);
			afficherPerso(p);
			afficherStats(p);
			SDL_UpdateRect(screen,0,0,0,0);
		}
	}
	//free
	destruction_grille(g);
	unsetImage();
	unsetObjet();
	unsetPerso(p);

	SDL_Quit();

}