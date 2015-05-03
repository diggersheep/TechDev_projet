/**
* @file personnage.h
* @brief proto personnage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#ifndef __PERSONNAGE_H_
#define __PERSONNAGE_H_
/*
#define OBJ_MAX 10
#define VARCHAR 256	
*/
//structure d'une position
typedef struct
{
	int x;
	int y;
} Pos;

/*
//structure d'un personnage
typedef struct
{
	Pos   pos;
	int   pv;
	int   pv_max;
	int   atk;
	int   def;
	Objet equip[5];
	char nom[VARCHAR];
	int  orientation;

} Perso;*/
/*
Pos get_pos (char *path);
Pos new_pos (int x, int y);
Objet new_objet (char nom[], int id, int pv, int atk, int def);
Perso new_perso (char nom[], Pos pos, int pv, int atk, int def);
*/

#endif