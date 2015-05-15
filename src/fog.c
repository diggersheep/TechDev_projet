/**
* @file fog.c
* @brief visibilité
* @author Alexandre COMBEAU, Alain KABBOUh
* @date 14-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <math.h>

#include "personnage.h"
#include "grille.h"
#include "fog.h"
#include "SDL_affichage.h"

grille grid_fog = NULL;
SDL_Surface* noir = NULL;

void initFogGrid (grille g)
{
	if (g == NULL)
	{
		printf("ErreurInitFogGrid: La grille n'est pas allouée (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}
	grid_fog = new_grille(g->n, g->m); //pas besoin de l'init a 0 grâce au Calloc de la fonction new_grille
	noir = SDL_LoadBMP("ressources/img/noir.bmp");
}

void FreeFogGrid (void)
{
	destruction_grille(grid_fog);
	SDL_FreeSurface(noir);
}

void unfogPerso (perso p)
{
	if (p == NULL)
	{
		printf("ErreurInitFogGrid: Le personnage n'est pas allouée (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	grid_fog->grid[p->pos.y][p->pos.x] = 1;
}

void afficherGrilleFog (void)
{
	unsigned int n;
	unsigned int m;

	for ( n = 0 ; n < grid_fog->n ; n++ )
	{
		for ( m = 0 ; m < grid_fog->m ; m++ )
			printf(" %d", grid_fog->grid[n][m]);
		printf("\n");
	}
}

void unfogCase (int n, int m, grille g)
{
	g->grid[n][m] = 1;
}

void unfogGrid (perso p, grille g, int dist)
{

	
	int n;
	int m;
	grille tmp = new_grille(g->n, g->m);

	for ( n = 0 ; n < grid_fog->n ; n++)
		for ( m = 0 ; m < grid_fog->m ; m++)
			tmp->grid[n][m] = grid_fog->grid[n][m];


	for ( n = 1 ; n < grid_fog->n-1 ; n++ )
	{
		for ( m = 1 ; m < grid_fog->m-1 ; m++ )
		{
			if (grid_fog->grid[n][m] == 1)
			{

				if ( g->grid[n+1][m] > 99 || g->grid[n+1][m] < 1 )
					if ( fabs(n + m + 1 - p->pos.x - p->pos.y) <= dist )
					{
						printf("Hello1\n");
						unfogCase(n+1, m, tmp);
					}

				if ( g->grid[n-1][m] > 99 || g->grid[n-1][m] < 1 )
					if ( fabs(n + m - 1 - p->pos.x - p->pos.y) <= dist )
					{
						printf("Hello2\n");
						unfogCase(n-1, m, tmp);
					}

				if ( g->grid[n][m+1] > 99 || g->grid[n][m+1] < 1 )
					if ( fabs(n + m + 1 - p->pos.x - p->pos.y) <= dist )
					{
						printf("Hello3\n");
						unfogCase(n, m+1, tmp);
					}

				if ( g->grid[n][m-1] > 99 || g->grid[n][m-1] < 1 )
					if ( fabs(n + m - 1 - p->pos.x - p->pos.y) <= dist )
					{

						printf("hello3\n");
						unfogCase(n, m-1, tmp);
					}
			}	
			
		}
	}
	
	for ( n = 0 ; n < grid_fog->n ; n++)
		for ( m = 0 ; m < grid_fog->m ; m++)
			grid_fog->grid[n][m] = tmp->grid[n][m];

	destruction_grille(tmp);	
}

void fogPrint (SDL_Surface* img)
{
	SDL_Rect tmp = screen_position;

	int n;
	int m;

	for ( n = 0 ; n < grid_fog->n ; n++)
		for ( m = 0 ; m < grid_fog->m ; m++)
		{
			screen_position.x = sceen_case_size * m;
			screen_position.y = sceen_case_size * n;
			if ( grid_fog->grid[n][m] == 0 )
			{
				printf("coucou\n");
				SDL_BlitSurface(img, NULL, screen, &screen_position);
			}
		}

	screen_position = tmp;
}
