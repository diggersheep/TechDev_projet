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

int game_state = 1;

SDL_Event screen_event;

int pause_touche ()
{
	int code = -9999;
	SDL_WaitEvent(&screen_event);
	switch (screen_event.type) // test le type d'event
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
					if (game_state == -1)
						code =-3;
					else
						code = 1;
					break;
				case SDLK_RIGHT :
					if (game_state == -1)
						code = -3;
					else
						code = 2;
					break;
				case SDLK_DOWN :
					if (game_state == -1)
						code =-3;
					else
						code = 3;
					break;
				case SDLK_LEFT :
					if (game_state == -1)
						code = -3;
					else
						code = 4;
					break;
				default:
					code = -3;
					break;
			}
			break;
	}

	return code;
}