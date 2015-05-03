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

int main (int argc, char *argv[])
{
	grille g = NULL;
	

	check_agrv(argc);
	
	g = mopen(argv[1]);


	destruction_grille(g);

	return 0;
}