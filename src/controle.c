/**
* @file controle.c
* @brief écoute du clavier et de la souris grâce aux événements SDL SDL
* @author Alexandre COMBEAU
* @date 02-05-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "controle.h"
#include "grille.h"

/*
//=========================================
//    VARIABLES GLOBALES POUR SDL
//=========================================
SDL_Surface* screen = NULL;               //context de la fenetre
SDL_Rect screen_position;                 //position dans la fenetre

unsigned int screen_size_l;               //taille de la fenetre
unsigned int screen_size_h;               //taille de la fenetre
unsigned int sceen_case_size = 32;        //taille d'une case en pixel

ObjScreen screen_image[MAX_SPRITE];       //banque d'image #hold-up X)
unsigned int screen_image_taille = 0;     //taille de la banque d'image
unsigned short chargemement_pourcent = 0; //indicateur barre de chargement
//=========================================
*/
int game_state = 1;

SDL_Event screen_event;

int pause_touche ()
{
	int code = -9999;
	SDL_WaitEvent(&screen_event);
	printf("... BITE\n");
	switch (screen_event.type) // test le tupe d'event
	{
		case SDL_QUIT:
        	code = -900000;
			break;
		case SDL_KEYDOWN:	
			switch(screen_event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					code = 0;
					break;
				case SDLK_q:
					code = 0;
					break;
				case SDLK_p:
					code = -1;
					game_state *= -1;
					break;
				case SDLK_r:
					code = -2;
					break;
				case SDLK_UP :
					code = 1;
					break;
				case SDLK_RIGHT :
					code = 2;
					break;
				case SDLK_DOWN :
					code = 3;
					break;
				case SDLK_LEFT :
					code = 4;
					break; 
			}
			break;
	}

	return code;
}
/*
int main(int argc, char *argv[])
{
	SDL_Event screen_event;
	unsigned int i;

	//init de la position
	screen_position.x = 0;
	screen_position.y = 0;
	
	//init grille
	grille g = NULL;
	g = mopen(argv[1]); 

	//inialisation du contexte de la fenetre SDL
	initSDL(g->n * sceen_case_size, g->m * sceen_case_size);

	//inialisation des images avec barre de chargement
	setAllImage();
	//indicateur de taille de la banque
	//printf("... screen_image_taille:%d\n", screen_image_taille);
	
	
	attendre_touche(); //Pause
	
	//Affichage de la grille ...
	SDL_AfficherGrille(g);
	SDL_Flip(screen); // <=> refresh();
	
	//Pause
	//attendre_touche();

	int code;
	do
	{
		code = pause_touche();
		printf("... ... code:%d\n", code);

	}
	while (code == -9999);

	//Désallocation mémoire !! Très important
	unsetImage();
	destruction_grille(g);

	return 0;
}*/