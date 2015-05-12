/**
* @file grille.c
* @brief fonctions grille
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grille.h"

#define MAX_LINE 256


grille new_grille (int n, int m)
{

	unsigned int i;
	grille       g = NULL;

	g = malloc(sizeof(Grille));	

	//test le bon fonctionnement de l'allcation
	if (g == NULL)
	{
		printf("ErreurNew_Grille : L'allocation de la grille a echoue(%p)\n", &g);
		exit(EXIT_FAILURE);
	}

	g->grid = (int**)malloc(sizeof(int*) * n);

	if (g->grid == NULL)
	{
		//test le bon fonctionnement de l'allocation
		printf("ErreurNew_Grille : L'allocation des donnees de la grille a echoue(%p)\n", &g->grid);
		free(g);
		exit(EXIT_FAILURE);
	}

	for (i = 0 ; i < n ; i++)
	{
		g->grid[i] = (int*)calloc(m , sizeof(int));
		if (g->grid[i] == NULL)
		{
			//test le bon fonctionnement des allocations
			printf("ErreurNew_Grille : L'allocation des donnees de la grille a echoue(%p)\n", &g->grid[i]);
			exit(EXIT_FAILURE);
		}
	}

	g->n = n;
	g->m = m;

	return g;
}


//désalloue la grille
void destruction_grille (grille lance)
{
	if (lance == NULL)
		return;

	unsigned int i;
	unsigned int j;

	for (i = 0 ; i < lance->n ; i++)
		free(lance->grid[i]);

	free(lance->grid);
	free(lance);

}

//Affiche la grille, mais c'est la version sans Ncurses
void afficher_grille (grille grid)
{
	unsigned int i;
	unsigned int j;

	for (i = 0 ; i < grid->n ; i++)
	{
		for (j = 0 ; j < grid->m ; j++)
		{
			if (grid->grid[i][j] == 0)
				printf("  ");
			else
				printf("%2d", grid->grid[i][j]);
		}
		printf("\n");
	}
}

//Map Open : permet de récupérer une map grace a un fichier *.map
grille mopen (char* path)
{	

	int    tmp;
	int    i;
	int    j;
	int    k;
	int    n;
	int    m;
	FILE*  f;
	grille grid = NULL;

	f = fopen(path, "r");
	i = 0;

	if (f != NULL)
	{

		while (!feof(f))
		{
			if (i == 0)
			{
				fscanf(f, " %d", &n);
				if (n <= 0)
				{
					printf("ErreurMopen : La valeur de la hauteur est invraissemblable - n:%d - %s (%p)\n",n, path,  &n);
					fclose(f);
					return NULL;
				}
			}
			else if (i == 1)
			{
				fscanf(f, " %d", &m);
				if (m <= 0)
				{
					printf("ErreurMopen : La valeur de la largeur est invraissemblable - m:%d - %s (%p)\n",m, path,  &m);
					fclose(f);
					return NULL;
				}
				grid = new_grille(n, m);
			}
			else if (i == 2 || i == 3)
			{
				//ne fait rien et c'est normal ! C'est la position du personnage
				fscanf(f, " %d", &tmp);
			}
			else
			{
				j = (i-4)/m;
				k = (i-4)%m;
				fscanf(f, " %d", &tmp);
				grid->grid[j][k] = tmp;
			}

			i++;
		}
	}
	else
	{
		printf("ErreurMopen : Le fichier n'a pas pu etre charge - %s (%p)\n", path,  &grid);
		destruction_grille(grid);
		exit(EXIT_FAILURE);
	}


	fclose(f);
	return grid;

}

void save_grille (grille g)
{
	if (g == NULL)
	{
		printf("ErreurSave_grille : La grille n'est pas initialisé (NULL) - (%p)\n", &g);
		return;
	}

	unsigned short i;
	unsigned int   hauteur;
	unsigned int   largeur;
	FILE*          f;
	FILE*          f2;
	char           path[64];

	printf("Indiquez le nom de la grille a sauvegarder (sans espaces) (extension .mat) : \n");
	scanf(" %s", path);

	f2 = fopen(path, "r");
	if (f2 != NULL)
	{
		printf("ErreurSave_grille : Le fichier que vous voulez créer existe déjà ");
		fclose(f2);
		return;
	}

	f = fopen(path, "w");

	if (f == NULL)
	{
		printf("ErreurSave_grille : Le fichier que vous voulez créer n'a pas pu être créé\n");
		return;
	}

	fprintf(f, "%d %d\n", g->n, g->m);

	for (hauteur = 0 ; hauteur < g->n ; hauteur++)
	{
		for (largeur = 0 ; largeur < g->m ; largeur++)
			fprintf(f, "%d ", g->grid[hauteur][largeur]);
		fprintf(f, "\n");
	}

	fclose(f);

}

void set_grille (grille g, int n, int m, int valeur)
{
	//===============================================
	//Tests de sureté pour faire remonter les erreurs
	if (g == NULL)
	{
		printf("ErreurSet_grille: La grille n'est pas allouée (NULL) - (%p)\n", &g);
		destruction_grille(g);
		exit(EXIT_FAILURE);
	}

	if (n > g->n || n <= 0)
	{
		printf("Erreurset_grille : La variable de \"n\" n'est pas comprise dans la grille (0-%d)- h:%d (%p)\n",g->n, n, &n);
		destruction_grille(g);
		exit(EXIT_FAILURE);
	}

	if (m > g->m || m <= 0)
	{
		printf("Erreurset_grille : La variable de \"m\" n'est pas comprise dans la grille (0-%d)- h:%d (%p)\n",g->m, m, &m);
		destruction_grille(g);
		exit(EXIT_FAILURE);
	}
	//===============================================

	g->grid[n - 1][m - 1] = valeur;

}

int info_grille (grille grid)
{	
	unsigned int i;
	unsigned int j;
	unsigned int count = 0;

	for (i = 0 ; i < grid->n ; i++)
	{
		for (j = 0 ; j < grid->m ; j++)
		{
			if (grid->grid[i][j] != 0)
			{
				count++;
			}
		}
	}

	return count;
}

void echangeGrille (grille g, int n, int m, int id)
{
	if (g == NULL)
	{
		printf("ErreurEchangeGrille : La grille n'exite pas (NULL) - (%p)\n", &g);
	}
	g->grid[n][m] = id;
}