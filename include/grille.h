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

typedef struct StrMapRessources
{
	unsigned int taille;
	char*        data[100];
}* map_ressourses;

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
/**Change la valeur d'une donnée de la grille connaissant ses coordonnées*/
void set_grille (grille g, int n, int m, int valeur);
/**Renvoie le nombre de cases non vide*/
int info_grille (grille grid);
/***/
map_ressourses map_loader(char* path);

#endif
