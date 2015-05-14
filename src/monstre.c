/**
* @file monstre.h
* @brief Monstre
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 04-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "grille.h"
#include "objet.h"
#include "personnage.h"
#include "monstre.h"

int      array_mob_screen_length = 0;
int      array_mob_length        = 0;


Mob_elem setMob (int pv, int atk, int def, short orientation, char* up, char* rigth, char* down, char* left, int id, unsigned short move)
{
	Mob_elem data;
	data.m    = setPerso (pv, atk,def, orientation, up, rigth, down, left);
	data.id   = id;
	data.move = move;

	return data;
}

void setAllMob (void)
{
	unsigned int max = 2;

	chargement(0, max);
	array_mob[array_mob_length] = setMob(10, 5, 5, 3, "ressources/img/mob/2000_0.bmp", "ressources/img/mob/2000_1.bmp", "ressources/img/mob/2000_2.bmp", "ressources/img/mob/2000_0.bmp", 2000, 1);
	array_mob_length++;
	chargement(1, max);
	array_mob[array_mob_length] = setMob(20, 1, 1, 3, "ressources/img/mob/2001_0.bmp", "ressources/img/mob/2001_1.bmp", "ressources/img/mob/2001_2.bmp", "ressources/img/mob/2001_0.bmp", 2001, 0);
	array_mob_length++;
	chargement(2, max);
}

void unsetMob (mob m) { unsetPerso(m); }

void unsetAllMob (void)
{
	unsigned int i;

	for (i = 0 ; i < array_mob_length ; i++)
	{
		if (array_mob[i].m != NULL)
		{
			unsetMob(array_mob[i].m);
		}
	}

	array_mob_length = 0;
	printf("Tous les monstres ont été désalloués\n");
}

int rechercheMob (int id)
{
	if (array_mob_length <= 0)
	{
		printf("ErreurRechercheMob: Il n'y a pas de monstres chargés : array_mob_length:%d\n", array_mob_length);
		exit(EXIT_FAILURE);
	}

	unsigned int i;

	for ( i = 0 ; i < array_mob_length ; i++ )
		if ( array_mob[i].id == id )
			return i;

	printf("ErreurRechercheMob: Le monstre que vous voulez n'est pas dans la liste des possibilités - id:%d\n", id);
}

void initMob (grille g, int id_remplacement)
{
	if ( g == NULL )
	{
		printf("ErreurInitMob: La grille n'existe pas (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}
	//array_mob_screen_length
	unsigned int n;
	unsigned int m;
	int id;
	Pos pos;

	for ( n = 0 ; n < g->n ; n++ )
		for ( m = 0 ; m < g->m ; m++ )
			if ( (g->grid[n][m] / 1000 ) == 2 )
			{
				//printf("Hello\n");
				id = rechercheMob(g->grid[n][m]);
				array_mob_screen[array_mob_screen_length] = array_mob[id];
				
				g->grid[n][m] = id_remplacement;
				//printf("... %d (id:%d)\n ", g->grid[n][m], array_mob_screen[array_mob_screen_length].m->pv);
				pos = newPos(m, n);
				setPersoPos(array_mob_screen[array_mob_screen_length].m, pos);

				array_mob_screen_length++;
			}
}
void killBob(mob m, int i)
{
	if (i != array_mob_screen_length)
		array_mob_screen[i] = array_mob_screen[array_mob_screen_length - 1];
	array_mob_screen_length--;
}



