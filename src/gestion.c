/**
* @file gestion.c
* @brief sources contenant les fonctions objet
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 03-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "grille.h"
#include "objet.h"
#include "personnage.h"
#include "gestion.h"
#include "SDL_affichage.h"
#include "monstre.h"
#include "deplacement.h"


void gameover (perso p, grille g)
{
	destruction_grille(g);
	unsetImage();
	unsetObjet();
	unsetPerso(p);
	unsetAllMob();

	SDL_Quit();
	exit(0);
}


Pos getNextCoord (perso p, grille g)
{
	if (g == NULL)
	{
		printf("ErreurgetNextCase : LA grille n'existe pas (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}

	//Je préfère ceci aux Switch/case, en C, c'est pas beau comme structure
	if (p->orientation == 0)
		return newPos(p->pos.y - 1,p->pos.x + 0);
	else if (p->orientation == 1)
		return newPos(p->pos.y + 0,p->pos.x + 1);
	else if (p->orientation == 2)
		return newPos(p->pos.y + 1,p->pos.x + 0);
	else if (p->orientation == 3)
		return newPos(p->pos.y + 0,p->pos.x - 1);
}


//============================================
//           OBJET
//============================================
void echangeObjet (Objet obj, int i, perso p)
{
	if (p == NULL)
	{
		printf("ErreurEchangeObjet: Le pointeur de personnage n'est pas alloué (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	p->equip[i] = obj;
}
void checkObjet(int id, int i, perso p)
{
	if (p == NULL)
	{
		printf("ErreurCheckObjet: Le pointeur de personnage n'est pas alloué (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	Objet obj = rechercheObjet(id);

	//printf("check\n");

	if( statsObjet(obj) > statsObjet(p->equip[i]))
	{
		//printf("OK\n");
		
		p->pv += obj.pv - p->equip[i].pv;
		p->pv_max += obj.pv - p->equip[i].pv;
		p->atk += obj.atk - p->equip[i].atk;
		p->def += obj.def - p->equip[i].def;
		
		echangeObjet(obj, i, p);
	}
}

void gestionObjet(int id, perso p, grille g)
{

	int divise = id - 1000 ;
	//printf("%d\n", divise);
	
	if (divise >= 0 & divise <= 999)
	{
	//	printf("oh ! un onjet (%d)\n", id);
	//	echangeGrille (g, p->pos.x, p->pos.y, 502);


		if (divise / 100 == 0)
			checkObjet(id, 0, p);
		else if (divise / 100 == 1)
			checkObjet(id, 0, p);
		else if (divise / 100 == 2)
			checkObjet(id, 1, p);
		else if (divise / 100 == 3)
			checkObjet(id, 2, p);
		else if (divise / 100 == 4)
			checkObjet(id, 3, p);
		else if (divise / 100 == 5)
			checkObjet(id, 4, p);
		
	}
}


//============================================
//           DEGAT/SOIN
//============================================

int degat (int atk, int def)
{
	//int subit = atk - (def / 5);
	int subit = atk - (def * 20) / 100;
	if (subit < 0)
		return 0;
	else
		return -1 * subit; //pour que ce soit negatif
}

int soin (int heal, int def)
{
	return heal + (def * 20) / 100;
}

void changePV (perso p, int x)
{
	if (p == NULL)
	{
		printf("ErreurChangePV : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	p->pv += x;

	if (p->pv > p->pv_max)
		p->pv = p->pv_max;
}


void gestionDegatperso (perso A, perso B, grille g)
{
	int fight  = 0;
	int subit = 0;

	if (A == NULL)
	{
		printf("ErreurChangePV : Le personnage n'existe pas (NULL) - (%p)\n", &A);
		exit(EXIT_FAILURE);
	}
	if (B == NULL)
	{
		printf("ErreurChangePV : Le personnage n'existe pas (NULL) - (%p)\n", &B);
		exit(EXIT_FAILURE);
	}

	if (A->pos.x+1 == B->pos.x && A->pos.y+0 == B->pos.y)
		fight = 1;
	if (A->pos.x-1 == B->pos.x && A->pos.y+0 == B->pos.y)
		fight = 1;
	if (A->pos.x+0 == B->pos.x && A->pos.y+1 == B->pos.y)
		fight = 1;
	if (A->pos.x+0 == B->pos.x && A->pos.y-1 == B->pos.y)
		fight = 1;

	if ( fight == 1 )
		subit = degat(A->atk, B->def);

	changePV(B, subit);
}

//============================================
//           Collision
//============================================
int gestionCollision (int id, perso p, int direction, int type)
{
	unsigned int i;

	if (id > 0 && id < 100) //cases de mur
		return 1;
	//array_mob_screen

	if (type == 0)
	{
		DeplacementPerso(p, direction);
		for ( i = 0 ; i < array_mob_screen_length ; ++i )
			if (p->pos.x == array_mob_screen[i].m->pos.x && p->pos.y == array_mob_screen[i].m->pos.y)
			{
				printf("... A>%d:%d M>%d:%d\n", p->pos.x, p->pos.y, array_mob_screen[i].m->pos.x, array_mob_screen[i].m->pos.y);
				DeplacementPerso(p, (direction+2)%4 );
				p->orientation = direction;
				return 1;
			}

		DeplacementPerso(p, (direction+2)%4 );
		p->orientation = direction;
	}

	return 0;
}

//============================================
//           Case de piege
//============================================
void gestionPiege (perso p, int id)
{
	if (p == NULL)
	{
		printf("ErreurGestionPiege : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	if (id / 100 == 1)
		changePV(p, degat(id - 100, p->def));
}
//============================================
//           Case de soin
//============================================
void gestionSoin (perso p, int id)
{
	if (p == NULL)
	{
		printf("ErreurGestionSoin : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	if (id / 100 == 2)
	{
		changePV(p, soin(id - 200, p->def));
		printf("vous avez été soigné !\n");
	}
}


//============================================
//           MORT/VIE
//============================================

bool mort (perso p)
{
	if (p == NULL)
	{
		printf("ErreurMort : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	if (p->pv <= 0)
		return 1;
	else 
		return 0;
}

void gestionVie (perso p, grille g, int type, int i)
{
	if (mort(p) == 1)
	{
		if (type == 0) //joueur
			gameover(p, g);
		else
			killBob(p, i);
	}
}



//============================================
//           Gagné
//============================================

void gagne (perso p, grille g)
{
	screen_position.x = 0;
	screen_position.y = 0;

	SDL_Delay(200);
	

	destruction_grille(g);
	unsetImage();
	unsetObjet();
	unsetPerso(p);
	unsetAllMob();

	SDL_Quit();
	exit(0);
}

void gestionGagne (perso p, grille g, int id)
{
	if (id == 777)
	 gagne(p, g);
}

//============================================
//           GESTION
//============================================

void gestion (grille g, perso p, int id, int type, int i)
{
	unsigned int j;

	gestionPiege(p, id);

	if (type == 0) // on ne va pas laisser les mobs se régénérés ni prendre des objets
	{
		gestionObjet(id, p, g);
		gestionSoin(p, id);
	}
	
	for ( j = 0 ; j < array_mob_screen_length ; j++ )
	{
		gestionDegatperso(array_mob_screen[j].m, p, g);
	}
	for ( j = 0 ; j < array_mob_screen_length ; j++ )
	{
		gestionDegatperso(p, array_mob_screen[j].m, g);
	}

	gestionVie(p, g, type, j);

	if (type == 0)
		gestionGagne(p, g, id);
}





