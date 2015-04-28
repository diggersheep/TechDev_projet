/**
* @file main.c
* @brief main
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

#define OBJ 12

int main (int argc, char *argv[])
{
	if (check_agrv(argc, argv) == 0) // test pour les agruments
	{

		Grille grid;
		Perso  joueur;
		Pos    pos;
		Objet  list_obj[OBJ];

		initscr();
		clear();

		//Ecran de chargement pour que ce soit beau ! :)

		printw("\n");
		printw("\n\n\n\t\t|                        |");
		printw("\n\t\t|                        |");
		refresh();
		napms(100);
		clear();

		grid = mopen(argv[1]);
		printw("\tLa grille a ete chargee\n");
		printw("\n\n\n\t\t|======                  |");
		printw("\n\t\t|======                  |");
		refresh();
		napms(300);
		clear();

		pos = get_pos(argv[1]);
		printw("La position est chargee a ete chargee\n");
		printw("\n\n\n\t\t|============            |");
		printw("\n\t\t|============            |");
		refresh();
		napms(300);
		clear();

		joueur = new_perso ("DiggerSheep", pos, 100, 10, 10);
		printw("Le personnage est charge\n");
		printw("\n\n\n\t\t|==================      |");
		printw("\n\t\t|==================      |");
		refresh();
		napms(300);
		clear();

		//Définitions des objet
		//epee
		list_obj[0] = new_objet("Epee flamboyante", 1002, 2, 0, 0);
		list_obj[1] = new_objet("Epee rien pour attendre", 1003, 4, 0, 2);
		//dague
		list_obj[2] = new_objet("Dague itahr", 1100, 2, 0, 0);
		list_obj[3] = new_objet("Dague du voleur volant", 1101, 4, 2, 0);
		//casque 
		list_obj[4] = new_objet("Casque du centurion baletus brossus", 1200, 0, 0, 5);
		list_obj[5] = new_objet("Heaume sweet heaume", 1201, 0, 2, 10);
		//armure 
		list_obj[6] = new_objet("Cotelette de maille", 1300, 0, 0, 5);
		list_obj[7] = new_objet("bretelles du guerrier", 1301, 0, 5, 30);
		//Bouclier
		list_obj[8] = new_objet("Casserole protectrice", 1400, 0, 2, 0);
		list_obj[9] = new_objet("Bouclier humain", 1401, 0, 5, 0);
		//botte
		list_obj[10] = new_objet("Boot en train", 1500, 1, 2, 5);
		list_obj[11] = new_objet("Spartiates de la bella italiana", 1501, 1, 1, 15);

		printw("Les objets sont charges\n");
		printw("\n\n");
		printw("\n\t\t|========================|");
		printw("\n\t\t|========================|");
		refresh();
		napms(300);
		
		printw("\n\nAppuyez sur \"c\" pour tester un chemin ou sur n'importe quelle autre pour commencer le jeu \n");
		refresh();
		char touche = getch();

		if (touche == 'c')
		{
			joueur = afficher_perso(grid, joueur, list_obj, OBJ);
			test_chemin(grid, joueur, list_obj, OBJ);
		}
		else
		{	
			//Boucle de jeu
			joueur = afficher_perso(grid, joueur, list_obj, OBJ);
			while (1)
			{
				joueur = get_dep(grid, joueur, list_obj, OBJ);
			}
		}

		

	}
	else
	{
		exit(1);
	}
	return 0;
}