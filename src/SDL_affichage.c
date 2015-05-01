/**
* @file SDL_affichage.c
* @brief affichage avec SDL
* @author Alexandre COMBEAU
* @date 01-05-2015
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "grille.h"

#define MAX_SPRITE 2000


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

void initSDL (int l, int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		exit(EXIT_FAILURE); //#DESTRUCTION !!!!!!!!!
	}

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(l, h, 32, SDL_SWSURFACE);

	screen_size_l = l;
	screen_size_h = h;
}

void attendre_touche (void)
{
	SDL_Event event;

	do
		SDL_WaitEvent(&event);
	while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}

void afficher_case (SDL_Surface* img)
{
	if(screen_position.x >= screen_size_l)
	{
		screen_position.x = 0;
		screen_position.y += sceen_case_size;
	}
	if(screen_position.y >= screen_size_h)
	{
		screen_position.x = 0;
		screen_position.y = 0;
		return;
	}

	SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format,0,0,0));
	SDL_BlitSurface(img, NULL, screen, &screen_position);

	screen_position.x += sceen_case_size;

}

void setImage (int id, char* path)
{
	if(screen_image_taille >= MAX_SPRITE)
		return;

	screen_image[screen_image_taille].img = SDL_LoadBMP(path);
	screen_image[screen_image_taille].id  = id;
	screen_image_taille++;
}


void chargemement (int current, int max)
{
	SDL_Rect pos_charg;
	SDL_Surface* rect1 = NULL;
	SDL_Surface* rect2 = NULL;
	SDL_Surface* barre = NULL;

	pos_charg.x = (screen_size_l / 2) - (204 / 2);
	pos_charg.y = (screen_size_h / 2) - (54 / 2);

	rect1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 204, 54, 32, 0, 0, 0, 0);
	SDL_SetColorKey(rect1, SDL_SRCCOLORKEY, SDL_MapRGB(rect1->format,0,0,0));
	SDL_FillRect(rect1, NULL, SDL_MapRGB(rect1->format, 163, 178, 174));
	SDL_BlitSurface(rect1, NULL, screen, &pos_charg); 


	pos_charg.x = (screen_size_l / 2) - (200 / 2);
	pos_charg.y = (screen_size_h / 2) - (50 / 2);


	rect2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 50, 32, 0, 0, 0, 0);
	SDL_SetColorKey(rect2, SDL_SRCCOLORKEY, SDL_MapRGB(rect2->format,0,0,0));
	SDL_FillRect(rect2, NULL, SDL_MapRGB(rect2->format, 17, 75, 66));
	SDL_BlitSurface(rect2, NULL, screen, &pos_charg); 

	chargemement_pourcent = current*100 / max;

	pos_charg.x = 0;
	pos_charg.y = 0;


	pos_charg.x = (screen_size_l / 2) - 100;
	pos_charg.y = (screen_size_h / 2) - (50 / 2);

	barre = SDL_CreateRGBSurface(SDL_HWSURFACE, 2*chargemement_pourcent, 50, 32, 0, 0, 0, 0);
	SDL_SetColorKey(barre, SDL_SRCCOLORKEY, SDL_MapRGB(barre->format,0,0,0));
	SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 76, 166, 142));
	SDL_BlitSurface(barre, NULL, screen, &pos_charg); 




	SDL_Flip(screen);
	SDL_FreeSurface(rect1);
	SDL_FreeSurface(rect2);
	SDL_FreeSurface(barre);

}

void setAllImage (void)
{
	int i;
	int j;

	int max = 607;

	chargemement(0, max);
	setImage(0, "../ressources/img/bmp/etoile.bmp");
	chargemement(1, max);

	setImage(1, "../ressources/img/bmp/mur.bmp");
	chargemement(2, max);

	for (i = 0 ; i < 100 ; i++)
	{
		setImage(200 + i+1, "../ressources/img/bmp/soin.bmp");
		chargemement(3+i, max);
	}

	setImage(500,"../ressources/img/bmp/sol.bmp");
	chargemement(4+i, max);
	
	setImage(501,"../ressources/img/bmp/sol2.bmp");
	chargemement(5+i, max);
	
	setImage(502,"../ressources/img/bmp/sol3.bmp");
	chargemement(6+i, max);

	for (j = 0 ; j < 500 ; j++)
	{
		setImage(1000+j,"../ressources/img/bmp/obj.bmp");
		chargemement(7+i+j, max);
	}
	setImage(510, "../ressources/img/bmp/black_hole.bmp");
	chargemement(8+i+j, max);
}


void unsetImage (void)
{
	while(screen_image_taille != 0)
	{
		SDL_FreeSurface(screen_image[screen_image_taille].img);
		screen_image_taille--;
	}
	printf("Toutes les images ont été désalouées\n");
}

void SDL_AfficherGrille(grille g)
{
	if (g == NULL)
	{
		printf("ErreurSDL_AfficherGrille : La grille est vide (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}

	unsigned int i;
	unsigned int j;
	unsigned int k;

	SDL_Surface* tmp = NULL;

	for (i = 0 ; i < g->n ; i++)
	{
		for (j = 0 ; j < g->m ; j++)
		{
			for(k = 0 ; k < screen_image_taille ; k++)
			{
				if (g->grid[i][j] == screen_image[k].id)
				{
					if (screen_image[k].img == NULL)
					{
						printf("ErreurSDL_AfficherGrille : Une image n'est pas chargée (NULL) - (%p)\n", &g);
						unsetImage();
						destruction_grille(g);
						exit(EXIT_FAILURE);
					}
					tmp = screen_image[k].img;
					k = 999999;//pour quitter la boucle
				}
			}
			if (tmp == NULL)
			{
				printf("ErreurSDL_AfficherGrille : Une image n'est pas chargée (NULL) - (%p)\n", &g);
				unsetImage();
				destruction_grille(g);
				exit(EXIT_FAILURE);
			}
			afficher_case(tmp);
		}
	}

	SDL_FreeSurface(tmp);

}


int main(int argc, char *argv[])
{
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
	attendre_touche();


	//Désallocation mémoire !! Très important
	unsetImage();
	destruction_grille(g);

	return 0;
}

/*



*/