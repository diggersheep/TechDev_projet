/**
* @file affichage.c
* @brief Affichage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "grille.old.h"
#include "personnage.old.h"
#include "affichage.old.h"

#define OBJ_MAX 10

//Affiche les différentes cases non blocantes
void gestion_case (Grille grid, int i, int j)
{
	if (grid.grid[i][j] / 100 == 1) //case piègées
	{
		printw("- ");
	}
	else if (grid.grid[i][j] / 100 == 2) //case de soins
	{
		printw("+ ");
	}
	else if (grid.grid[i][j] / 1000 == 1) //case contenant des objets
	{
		printw("! ");
	}
	else
	{
		printw("  ");
	}
}

//gestion centralisés de toute la grille
Persoold gesion (Grille grid, int i, int j, Persoold perso, Objetold obj[], int taille_obj)
{
	
	if (grid.grid[i][j] / 100 == 1) //case piègées
	{
		perso.pv -= (grid.grid[i][j] - 100);
		if (perso.pv <= 0)
			perdu(grid, perso);
	}
	else if (grid.grid[i][j] / 100 == 2) //case de soins
	{
		perso.pv += (grid.grid[i][j] - 200);
		if (perso.pv > perso.pv_max)
			perso.pv = perso.pv_max;
	}
	else if (grid.grid[i][j] / 1000 == 1)
	{
		perso = gestion_objet(grid, i, j, perso, obj, taille_obj);
	}

	return perso;	
}

//Fonction explicite
Persoold change_objet (Persoold perso, Objetold old,Objetold new)
{
	perso.pv += (new.pv - old.pv);
	perso.pv_max += (new.pv - old.pv);
	perso.atk += (new.atk - old.atk);
	perso.def += (new.def - old.def);
	return perso;
}

//Fonction qui permet de récuperer les objets et les assiges direcrement dans l'inventaire selon leur carac
//Bon ... C'est pas super optimal en terme de longueur, mais chaque partie fait la meme chose
Persoold gestion_objet (Grille grid, int n, int m, Persoold perso, Objetold obj[], int taille_obj)
{
	int i;

	if(grid.grid[n][m] / 100 == 10 || grid.grid[n][m] / 100 == 11)
	{
		//epee + dague
		if (perso.equip[0].id == 1001)
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					perso = change_objet(perso, perso.equip[0], obj[i]);
					perso.equip[0] = obj[i];
					i = 1000000;
					obj2void(grid, n, m);
				}
			}
		}
		else 
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					if (perso.equip[0].atk < obj[i].atk)
					{
						perso = change_objet(perso, perso.equip[0], obj[i]);
						perso.equip[0] = obj[i];
						obj2void(grid, n, m);
					}
					i = 1000000;
				}
			}
	

		}
	}
	else if (grid.grid[n][m] / 100 == 12)
	{
		//casque
		if (perso.equip[2].id == 1001)
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					perso = change_objet(perso, perso.equip[2], obj[i]);
					perso.equip[2] = obj[i];
					obj2void(grid, n, m);
					i = 1000000;
				}
			}
		}
		else 
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					if (perso.equip[2].pv < obj[i].pv)
					{
						perso = change_objet(perso, perso.equip[2], obj[i]);
						obj2void(grid, n, m);
						perso.equip[2] = obj[i];
					}
					i = 1000000;
				}
			}
	

		}
	}
	else if (grid.grid[n][m] / 100 == 13)
	{
		//armures
		if (perso.equip[3].id == 1001)
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					perso = change_objet(perso, perso.equip[3], obj[i]);
						obj2void(grid, n, m);
					perso.equip[3] = obj[i];
					i = 1000000;
				}
			}
		}
		else 
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					if (perso.equip[3].def < obj[i].def)
					{
						perso = change_objet(perso, perso.equip[3], obj[i]);
						obj2void(grid, n, m);
						perso.equip[3] = obj[i];
					}
					i = 1000000;
				}
			}
	

		}
	}
	else if (grid.grid[n][m] / 100 == 14)
	{
		//bouclier
		if (perso.equip[1].id == 1001)
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					perso = change_objet(perso, perso.equip[1], obj[i]);
						obj2void(grid, n, m);
					perso.equip[1] = obj[i];
					i = 1000000;
				}
			}
		}
		else 
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					if (perso.equip[1].def < obj[i].def)
					{
						perso = change_objet(perso, perso.equip[1], obj[i]);
						obj2void(grid, n, m);
						perso.equip[1] = obj[i];
					}
					i = 1000000;
				}
			}
	

		}
	}
	else if (grid.grid[n][m] / 100 == 15)
	{
		//botte
		if (perso.equip[4].id == 1001)
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					perso = change_objet(perso, perso.equip[4], obj[i]);
						obj2void(grid, n, m);
					perso.equip[4] = obj[i];
					i = 1000000;
				}
			}
		}
		else 
		{
			for (i = 0 ; i < taille_obj ; i++)
			{
				if(obj[i].id == grid.grid[n][m])
				{
					if ( (perso.equip[4].def+perso.equip[4].atk+perso.equip[4].pv) < (obj[i].def+obj[i].atk+obj[i].pv ))
					{
						perso = change_objet(perso, perso.equip[4], obj[i]);
						obj2void(grid, n, m);
						perso.equip[4] = obj[i];
					}
					i = 1000000;
				}
			}
	

		}
	}
	return perso;
}

//Fonction pour flemmard !
void obj2void (Grille grid, int i, int j)
{
	grid.grid[i][j] = 0;
}

//Affiche les stats du perso en dessous de la grille
void stats_perso (Persoold perso)
{
	int i;
	int vie;

	vie = perso.pv / (int)(perso.pv_max/10);
	
	printw("\n");
	printw("Nom : %s\t", perso.nom);
	printw("[%3d/%3d : ", perso.pv, perso.pv_max);
	
	for (i = 1 ; i <= 10 ; i++)
	{
		if (i <= vie)
		{
			printw("|");
		}
		else
		{
			printw(" ");
		}
	}

	printw("]");
	printw("\n");
	printw("ATK : %d\t", perso.atk);
	printw("DEF : %d\n", perso.def);
	printw("\n #  atk  def  vie  nom\n");
	for(i = 0 ; i < 5 ; i++)
	{
		printw("%2d  %2d   %2d   %2d   %s\n", i+1, perso.equip[i].atk, perso.equip[i].def, perso.equip[i].pv, perso.equip[i].nom);
	}
}

//Affiche la grille du personnage et les stats
Persoold afficher_perso (Grille grid, Persoold P, Objetold obj[], int taille_obj)
{
	clear();
	int i;
	int j;
	int ascii;

	
	clear();

	for (i = 0 ; i < grid.n ; i++)
	{
		for (j = 0 ; j < grid.m ; j++)
		{


			if (grid.grid[i][j] != 1 && grid.grid[i][j] != 2)
			{
				if (i == (P.pos.x - 1) && j == (P.pos.y - 1))
				{
					if (P.orientation == 0)
						printw("^ ");
					else if (P.orientation == 1)
						printw("> ");
					else if (P.orientation == 2)
						printw("v ");
					else if (P.orientation == 3)
						printw("< ");

					P = gesion(grid, i, j, P, obj, taille_obj);
				}
				else
					gestion_case(grid, i, j);
			}
			else if (grid.grid[i][j] != 1)
			{
				printw("~ ");
			}
			else
			{
				printw ("# ");
			}


		}
		printw("\n");
	}
	
	stats_perso(P);
	refresh();
	return P;
}

//fonction centrale du jeu. Elle permet de capturer une touche et de déplacer le personnage
//Elle utilise "gestion" et "afficher_perso"
Persoold get_dep (Grille grid, Persoold perso, Objetold obj[], int taille_obj)
{
	char touches = getch();

	int left  = grid.grid[perso.pos.x - 1][perso.pos.y - 2];
	int right = grid.grid[perso.pos.x - 1][perso.pos.y    ];
	int up    = grid.grid[perso.pos.x - 2][perso.pos.y - 1];
	int down  = grid.grid[perso.pos.x    ][perso.pos.y - 1];

	
	if (touches == 'z')
	{

		perso.orientation = 0;

		if (up != 1 && up != 2)
		{
			--perso.pos.x;
		}

		perso = afficher_perso(grid, perso, obj, taille_obj);


	}
	else if (touches == 's')
	{
		perso.orientation = 2;
		if (down != 1 && down != 2)
		{
			++perso.pos.x;
		}

		perso = afficher_perso(grid, perso, obj, taille_obj);

	}
	else if (touches == 'q')
	{
		perso.orientation = 3;
		if (left != 1 && left != 2)
		{
			--perso.pos.y;
		}


		perso = afficher_perso(grid, perso, obj, taille_obj);

	}
	else if (touches == 'd')
	{
		perso.orientation = 1;
		if (right != 1 && right != 2)
		{
			++perso.pos.y;
		}

		perso = afficher_perso(grid, perso, obj, taille_obj);

	}
	else if (touches == '\n')
	{	
		refresh();
		endwin();
		destruction_grille(grid);
		exit(0);
	}
	else
	{
		afficher_perso(grid, perso, obj, taille_obj);
	}

	return perso;
}

//Fonction qui fait perdre
void perdu (Grille grid, Persoold perso)
{
	clear();
	printw("Vous avez perdu :(");
	refresh();
	napms(1000);

	endwin();
	destruction_grille(grid);
	exit(0);
}

