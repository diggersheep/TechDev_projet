/**
* @file personnage.c
* @brief description d'un personnage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grille.old.h"
#include "personnage.old.h"

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

//défini un nouvel objet
Objetold new_objet (char nom[], int id, int atk, int def, int pv)
{
	Objetold obj;	
	strcpy(obj.nom, nom);

	obj.id     = id;
	obj.pv     = pv;
	obj.atk    = atk;
	obj.def    = def;

	return obj;
}

//défini un nouveau personnage
Persoold new_perso (char nom[], Pos pos, int pv, int atk, int def)
{
	int i;

	Persoold P;
	Objetold obj_null = new_objet(" ", 1001, 0, 0, 0);

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
