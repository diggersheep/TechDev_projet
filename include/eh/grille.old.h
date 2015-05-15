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

Grille  newgrille         (int n, int m);
void    destructiongrille (Grille style);
void    affichergrille    (Grille grid);
Grille  mopenold          (char* path);
#endif
