/**
* @file objet.c
* @brief sources contenant les fonctions objet
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 03-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

#include "objet.h"
#include "SDL_affichage.h"

#define VARCHAR 256

unsigned int object_array_length = 0;

void setObjet(char nom[], char* path, int id, int pv, int atk, int def)
{	
	if (object_array_length >= 1000)
	{	
		printf("WarningNew_objet : Toutes les cases de skotages d'objets sont utilisés, il ne peux y en avoir plus\n");
		return;
	}

	strcpy(object_array[object_array_length].nom, nom);

	object_array[object_array_length].id  = id;
	object_array[object_array_length].pv  = pv;
	object_array[object_array_length].def = def;
	object_array[object_array_length].atk = atk;
	object_array[object_array_length].img = SDL_LoadBMP(path);

	object_array_length++;
}

void setAllObjet (void)
{	
	int max = 13;
	int i;
	chargement(0,max);
	setObjet(" ", "ressources/img/obj/1000.bmp", 1000, 0, 0, 0);
	chargement(1,max);
	setObjet("Sabre grille-pain", "ressources/img/obj/1001.bmp",1001, 0, 5, 0);
	chargement(2,max);
	setObjet("Epee rien pour attendre", "ressources/img/obj/1002.bmp",1001, 0, 10, 2);
	chargement(3,max);

	setObjet("Glaive de l'alligator", "ressources/img/obj/1100.bmp",1100, 0, 5, 2);
	chargement(4,max);
	setObjet("Dague du voleur volant", "ressources/img/obj/1101.bmp",1101, 5, 8, 2);
	chargement(5,max);

	setObjet("Casque Astronomique", "ressources/img/obj/1200.bmp",1200, 5, 0, 0);
	chargement(6,max);
	setObjet("Casque invisible", "ressources/img/obj/1201.bmp",1201, 10, 0, 2);
	chargement(7,max);
	setObjet("Couvre-moche", "ressources/img/obj/1202.bmp",1202, 30, 0, 5);
	chargement(8,max);
	
	setObjet("Cotetlette de maille", "ressources/img/obj/1300.bmp",1300, 0, 0, 5);
	chargement(9,max);
	setObjet("Cape de l'apprenti jet d'ail", "ressources/img/obj/1301.bmp",1301, 2, 0, 10);
	chargement(10,max);
	setObjet("bretelles du guerrier fringant", "ressources/img/obj/1302.bmp",1302, 0, 4, 20);
	chargement(11,max);

	setObjet("Bouclier humain", "ressources/img/obj/1400.bmp",1400, 0, 0, 10);
	chargement(12,max);
	setObjet("Wookie Luck", "ressources/img/obj/1401.bmp",1401, 1, 5, 15);
	chargement(13,max);
	


	setObjet(" ", "ressources/img/obj/1000.bmp", 1000, 0, 0, 0);
	setObjet(" ", "ressources/img/obj/1000.bmp", 1000, 0, 0, 0);

	for (i = 0 ; i < max ; i++)
	{
		if (object_array[i].img == NULL)
		{
			printf("ErreurSetAllObjet: Image null (n. %d)\n", i+1);
			exit(EXIT_FAILURE);
		}
	}
}

void unsetObjet (void)
{
	while(object_array_length > 0)
	{
		object_array_length--;
		SDL_FreeSurface(object_array[object_array_length].img);
	}
}

Objet rechercheObjet (int id)
{
	if (id < 1000 && id > 1999)
	{
		printf("Erreurrechercehobjet: L'id n'est pas un objet - id:%d\n", id);
		exit(EXIT_FAILURE);
	}
	int i;
	for (i = 0 ; i < object_array_length ; i++)
	{
		if (object_array[i].id == id)
		{
	//		printf("> %d\n", object_array[i].id);
			return object_array[i];
		}
	}

	printf("ErreurRechercehObjet: l'objet pas dans  - id:%d\n", id);
	exit(EXIT_FAILURE);
}

int statsObjet(Objet obj)
{
	return (obj.pv + obj.atk + obj.def);
}