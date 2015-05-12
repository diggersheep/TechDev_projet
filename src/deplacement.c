#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "grille.h"
#include "personnage.h"
#include "deplacement.h"
#include "gestion.h"


int getDepGrille (perso p, grille g, int direction)
{
	if (p == NULL)
	{
		printf("ErreurGetDepGrille : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	if (g == NULL)
	{
		printf("ErreurGetDepGrille : LA grille n'existe pas (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}

	if (direction == 0)
		return g->grid[p->pos.y - 1][p->pos.x + 0];
	else if (direction == 1)
		return g->grid[p->pos.y + 0][p->pos.x + 1];
	else if (direction == 2)
		return g->grid[p->pos.y + 1][p->pos.x + 0];
	else if (direction == 3)
		return g->grid[p->pos.y + 0][p->pos.x - 1];
}

void DeplacementPerso (perso p, int direction)
{
	if (p == NULL)
	{
		printf("ErreurDeplacement : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	if (direction == 0)
		p->pos.y--;
	else if (direction == 1)
		p->pos.x++;
	else if (direction == 2)
		p->pos.y++;
	else if (direction == 3)
		p->pos.x--;
}

void GetDeplacementPerso (perso p, int type, grille g, int direction)
{
	int id = -9999;
	if (p == NULL)
	{
		printf("ErreurDeplacerPerso : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	if (g == NULL)
	{
		printf("ErreurDeplacerPerso : La grille n'existe pas (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}


	if (direction >= 0 && direction <= 3)
		id = getDepGrille(p, g, direction);
	else
	{
		printf("WarningGetDeplacementPerso : aucunes direction ... \n");
		return;
	}

	p->orientation = direction;

	printf("... ... %d \n", /*gestionCollision(id),*/ id);

	if (gestionCollision(id) == 1)
		return;

	DeplacementPerso(p, direction);

}

