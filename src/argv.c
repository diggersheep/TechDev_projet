/**
* @file argv.c
* @brief Arguments systeme
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#include <stdio.h>
#include <stdlib.h>

//test le nombre d'arguments
int check_agrv (int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("Erreur : Il n'y a  pas assez d'argument\n");
		return 1;
	}
	else if (argc == 2)
	{
		return 0;
	}
	else
	{
		printf("Erreur : Il y a trop d'arguments\n");
		return 1;
	}
}