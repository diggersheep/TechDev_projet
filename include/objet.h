/**
* @file objet.h
* @brief proto objet
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 03-05-2015
*/

#ifndef __OBJET_H_
#define __OBJET_H_

#define VARCHAR 256

typedef struct
{
	char nom[VARCHAR];
	int  id;
	int  pv;
	int  atk;
	int  def;
	SDL_Surface* img;
} Objet;

typedef Objet *objet;

void  UnsetObjet  (void);
void  setObjet    (char nom[], char* path, int id, int pv, int atk, int def);
void  setAllObjet (void);
#endif