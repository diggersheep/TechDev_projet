/**
* @file chemin.c
* @brief Test de chemin
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "grille.h"
#include "personnage.h"
#include "affichage.h"
/*
#define N 20
//Si le chemin est invalide
void path_fail (Grille grid)
{
		clear();
		printw("Le chemin n'est pas valide\n");
		refresh();
		getch();

		endwin();
		destruction_grille(grid);
		exit(0);
}

//si le chmin est valide
void path_pass (Grille grid)
{

		clear();
		printw("Le chemin est valide\n");
		refresh();
		getch();

		endwin();
		destruction_grille(grid);
		exit(0);
}

Perso get_chemin (Grille grid, Perso perso, Objet obj[], int taille_obj, char touches)
{
	int left  = grid.grid[perso.pos.x - 1][perso.pos.y - 2];
	int right = grid.grid[perso.pos.x - 1][perso.pos.y    ];
	int up    = grid.grid[perso.pos.x - 2][perso.pos.y - 1];
	int down  = grid.grid[perso.pos.x    ][perso.pos.y - 1];

	
	if (touches == 'z')
	{

		perso.orientation = 0;

		if (up != 1 || up != 2)
		{
			--perso.pos.x;
		}
		else
		{
			path_fail(grid);
		}

		perso = afficher_perso(grid, perso, obj, taille_obj);


	}
	else if (touches == 's')
	{
		perso.orientation = 2;
		if (down != 1|| down != 2)
		{
			++perso.pos.x;
		}
		else
		{
			path_fail(grid);
		}

		perso = afficher_perso(grid, perso, obj, taille_obj);

	}
	else if (touches == 'q')
	{
		perso.orientation = 3;
		if (left != 1 || left != 2)
		{
			--perso.pos.y;
		}
		else
		{
			path_fail(grid);
		}


		perso = afficher_perso(grid, perso, obj, taille_obj);

	}
	else if (touches == 'd')
	{
		perso.orientation = 1;
		if (right != 1 || right != 2)
		{
			++perso.pos.y;
		}
		else
		{
			path_fail(grid);
		}

		perso = afficher_perso(grid, perso, obj, taille_obj);
	return perso;
}
}

void test_chemin (Grille grid, Perso perso, Objet obj[], int taille_obj)
{
	FILE*  f;
	char touches;
	int i;

	char chemin[] = "ssqszszszszszszszszs";

	for (i = 0; i < N; i++)
	{
		get_chemin (grid, perso, obj, taille_obj, chemin[i]);
	}
	path_pass(grid);
}*/