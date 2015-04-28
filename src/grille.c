/**
* @file grille.c
* @brief fonctions grille
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include "grille.h"

#define MAX_LINE 512

void new_line (void)
{
	printf("\n");
}


Grille new_grille (int n, int m)
{
	// Crée une nouvelle grille de taille N*M
	Grille g;
	g.n = n;
	g.m = m;
	int i;

	g.grid = (int**)malloc(n * sizeof(int*) );

	for (i = 0 ; i < n ; i++)
		g.grid[i] = (int*)calloc(m , sizeof(int));
	
	return g;
}


//désalloue la grille
void destruction_grille (Grille lance)
{
	int i ;
	for (i = 0 ; i < lance.n ; i++)
	{
		free(lance.grid[i]);
	}
	free(lance.grid);
	
	lance.n = 0;
	lance.m = 0;

}

//Affiche la grille, mais c'est la version sans Ncurses
void afficher_grille (Grille grid)
{
	int i;
	int j;

	for (i = 0 ; i < grid.n ; i++)
	{
		for (j = 0 ; j < grid.m ; j++)
		{
			if (grid.grid[i][j] == 0)
				printf("  ");
			else
				printf("%2d", grid.grid[i][j]);
		}
		printf("\n");
	}
}

//Map Open : permet de récupérer une map grace a un fichier *.map
Grille mopen (char* path)
{	

	int    tmp;
	int    i;
	int    j;
	int    k;
	int    n;
	int    m;
	FILE*  f;
	Grille grid;

	f = fopen(path, "r");
	i = 0;

	if (f != NULL)
	{

		while (!feof(f))
		{
			if (i == 0)
				fscanf(f, " %d", &n);
			else if (i == 1)
			{
				fscanf(f, " %d", &m);
				grid = new_grille(n, m);
			}
			else if (i == 2)
			{
				fscanf(f, " %d", &tmp);
			}
			else if (i == 3)
			{
				fscanf(f, " %d", &tmp);
			}
			else
			{
				j = (i-4)/m;
				k = (i-4)%m;
				fscanf(f, " %d", &tmp);
				grid.grid[j][k] = tmp;
			}

			i++;
		}
	}
	else
	{
		printf("Erreur : Le fichier n'a pas pu etre charge !\n");
		exit(1);
	}


	fclose(f);
	return grid;

}

int info_grille (Grille grid)
{	
	unsigned int i;
	unsigned int j;
	unsigned int count = 0;

	for (i = 0 ; i < grid.n ; i++)
	{
		for (j = 0 ; j < grid.m ; j++)
		{
			if (grid.grid[i][j] != 0)
			{
				count++;
			}
		}
	}

	return count;
}