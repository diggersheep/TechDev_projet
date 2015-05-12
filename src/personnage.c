/**
* @file personnage.c
* @brief description d'un personnage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grille.h"
#include "SDL_affichage.h"
#include "controle.h"
#include "objet.h"
#include "personnage.h"


#define VARCHAR 256


/** @brief défini une nouvelle positon*/
Pos newPos (int x, int y)
{
	Pos P;
	
	P.x = x;
	P.y = y;
	return P;
}

//Permet de récupérer une paire de coordonnée grace a un fichier *.map
Pos getPos (char *path)
{
	FILE*  f;
	Pos pos;
	int i;
	int z;
	f = fopen(path, "r");
	i = 0;

	if (f != NULL)
	{

		for (i = 0 ; i < 4 ; i++)
		{
			if (i == 2)
			{
				fscanf(f, " %d", &pos.x);
			}
			else if (i == 3)
			{
				fscanf(f, " %d", &pos.y);
			}
			else
			{
				fscanf(f, " %d", &z);
			}

		}
		fclose(f);
		return pos;
	}
	else
	{
		fclose(f);
		printf("Erreur : Le fichier n'a pas pu etre charge !\n");
		exit(1);
	}
}

perso setPerso (int pv, int atk, int def,short orientation, char* up, char* right, char* down, char* left)
{
	perso p = malloc(sizeof(Perso));

	if (p == NULL)
	{
		printf("ErreurSetPerso : Le personnage n'a pas été alloué (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	if (orientation < 0 && orientation > 3)
	{
		printf("Warning : Orientation invraissemblable (0-4) - orientation:%d\n", orientation);
		orientation = 0;
	}

	short i;

	p->pv          = pv;
	p->pv_max      = pv;
	p->atk         = atk;
	p->def         = def;
	p->orientation = orientation;

	Objet obj = rechercheObjet(1000); //Objet par défaut, sans caractéristiques

	for (i = 0 ; i < 5 ; i++)
	{
		p->equip[i] = rechercheObjet(1000);
	}


	p->img[0] = SDL_LoadBMP(up);
	p->img[1] = SDL_LoadBMP(right);
	p->img[2] = SDL_LoadBMP(down);
	p->img[3] = SDL_LoadBMP(left);


	return p;
}

void unsetPerso (perso p)
{
	SDL_FreeSurface(p->img[0]);
	SDL_FreeSurface(p->img[1]);
	SDL_FreeSurface(p->img[2]);
	SDL_FreeSurface(p->img[3]);
	
	free(p);
}

void setPersoPos (perso p, Pos coord)
{
	if (p == NULL)
	{
		printf("ErreurSetPersoPos : Le personnage n'existe pas (NULL) - (%p)\n", &p);
	}
	p->pos = coord;
}