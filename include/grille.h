/**
* @file grille.h
* @brief proto grille
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#ifndef __GRILLE_H_
#define __GRILLE_H_
typedef struct
{
	int n;
	int m;
	int** grid;
}Grille;

Grille  new_grille         (int n, int m);
void    destruction_grille (Grille style);
void    afficher_grille    (Grille grid);
Grille  mopen              (char* path);
int     info_grille        (Grille grid);
#endif
