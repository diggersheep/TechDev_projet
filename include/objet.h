/**
* @file objet.h
* @brief proto objet
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 03-05-2015
*/

#ifndef __OBJET_H_
#define __OBJET_H_



#define VARCHAR 256
#define OBJ_MAX 1000

typedef struct
{
	char nom[VARCHAR];
	int  id;
	int  pv;
	int  atk;
	int  def;
	SDL_Surface* img;
} Objet;

Objet object_array[OBJ_MAX];
unsigned int object_array_length;

/**Fonction qui défini un nouvel objet dans le jeu*/
void setObjet(char nom[], char* path, int id, int pv, int atk, int def);
/**Fonction qui à l'aide de "setObjet" défini tous les objets du jeu*/
void setAllObjet (void);
/**Fonction qui désalloue toutes les images des objets*/
void unsetObjet (void);
/**Fonction qui a partir d'un id cherche l'objet associé*/
Objet rechercheObjet (int id);
/**Renvoie la somme des stats de l'objet*/
int statsObjet(Objet obj);

#endif