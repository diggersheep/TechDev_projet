/**
* @file personnage.c
* @brief description d'un personnage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "personnage.h"
#include "grille.h"
#include "SDL_affichage.h"
#include "controle.h"
#include "objet.h"


#define OBJ_MAX 10
#define VARCHAR 256

/** @brief défini une nouvelle positon
* @param int x et in y
* @return position
*/
Pos new_pos (int x, int y)
{
	Pos P;
	
	P.x = x;
	P.y = y;
	return P;
}


//Permet de récupérer une paire de coordonnée grace a un fichier *.map
Pos get_pos (char *path)
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

/*
//défini un nouveau personnage
Perso new_perso (char nom[], Pos pos, int pv, int atk, int def)
{
	int i;

	Perso P;
	Objet obj_null = new_objet(" ", 1001, 0, 0, 0, );

	strcpy(P.nom, nom);
	P.pos.x = pos.x;
	P.pos.y = pos.y;
	P.pv     = pv;
	P.pv_max = pv;
	P.atk    = atk;
	P.def    = def;
	P.orientation = 0;

	for (i = 0 ; i < 5 ; i++)
	{
		P.equip[i] = obj_null;
	}

	return P;
}*/


int main(int argc, char *argv[])
{
	SDL_Event screen_event;
	unsigned int i;

	//init de la position
	screen_position.x = 0;
	screen_position.y = 0;
	
	//init grille
	grille g = NULL;
	g = mopen(argv[1]); 

	//inialisation du contexte de la fenetre SDL
	initSDL(g->n * sceen_case_size, g->m * sceen_case_size);

	//inialisation des images avec barre de chargement, de meme pour les images d'objet
	setAllImage();
	setAllObjet();

	//indicateur de taille de la banque
	//printf("... screen_image_taille:%d\n", screen_image_taille);
	
	
	attendre_touche(); //Pause
	
	//Affichage de la grille ...
	SDL_AfficherGrille(g);
	SDL_Flip(screen); // <=> refresh();
	
	//Pause
	//attendre_touche();

	int code;
	do
	{
		code = pause_touche();
		printf("... ... code:%d\n", code);

	}
	while (code == -9999);

	//Désallocation mémoire !! Très important
	unsetImage();
	unsetObjet();
	destruction_grille(g);

	return 0;
}