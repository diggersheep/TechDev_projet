/**
* @file grille.h
* @brief proto grille
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#ifndef __GRILLE_H_
#define __GRILLE_H_

#define MAX_LINE 256

/**Structure de la grille*/
typedef struct
{
	int   n;
	int   m;
	int** grid;
}Grille;

typedef Grille* grille;
typedef char* string;

/**Alloue une nouvelle grille vide*/
grille new_grille (int n, int m);
/**désalloue la grille*/
void destruction_grille (grille lance);
/**Affiche la grille, mais c'est la version sans Ncurses*/
void afficher_grille (grille grid);
/**Map Open : permet de récupérer une map grace a un fichier *.map*/
grille mopen (char* path);
void save_grille (grille g);
/**Renvoie le nombre de cases non vide*/
int info_grille (grille grid);
/**Change la valeur d'un entier dans la grille*/
void echangeGrille (grille g, int n, int m, int id);

#endif
