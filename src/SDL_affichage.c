#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "grille.h"

#define MAX_SPRITE 2000


typedef struct StrObjScreen
{
	int id;
	SDL_Surface* img;
} ObjScreen;

SDL_Surface* screen = NULL;
SDL_Rect screen_position;

unsigned int screen_size_l;
unsigned int screen_size_h;
unsigned int sceen_case_size = 32;

ObjScreen screen_image[MAX_SPRITE];
unsigned int screen_image_taille = 0;
unsigned short chargemement_pourcent = 0;

void initSDL (int l, int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		exit(EXIT_FAILURE);
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
	unsigned int i;
	unsigned int j;
	unsigned int k;

	SDL_Surface* tmp;

	for (i = 0 ; i < g->n ; i++)
	{
		for (j = 0 ; j < g->m ; j++)
		{
			for(k = 0 ; k < screen_image_taille ; k++)
			{
				if (g->grid[i][j] == screen_image[k].id)
				{
					tmp = screen_image[k].img;
					k = 999999;
				}
			}
			afficher_case(tmp);
		}
	}

	SDL_FreeSurface(tmp);

}


int main(int argc, char *argv[])
{
	unsigned int i;

	screen_position.x = 0;
	screen_position.y = 0;
	
	grille g = NULL;
	//sprite
	SDL_Surface* fond = NULL;
	SDL_Surface* obj = NULL;
	SDL_Surface* sol = NULL;
	SDL_Surface* etoile = NULL;

	g = mopen(argv[1]); 

	initSDL(g->n * sceen_case_size, g->m * sceen_case_size);

	setAllImage();	
	printf("... screen_image_taille:%d\n", screen_image_taille);
	attendre_touche();
	
	SDL_AfficherGrille(g);
	SDL_Flip(screen);
	attendre_touche();

	unsetImage();
	destruction_grille(g);

	return 0;
}