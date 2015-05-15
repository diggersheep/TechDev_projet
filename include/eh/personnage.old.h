/**
* @file personnage.h
* @brief proto personnage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#ifndef __PERSONNAGE_H_
#define __PERSONNAGE_H_

#define OBJ_MAX 10
#define VARCHAR 256	

//structure d'une position
typedef struct
{
	int x;
	int y;
} Pos;


//structure d'un objet
typedef struct
{
	char nom[VARCHAR];
	int  id;
	int  pv;
	int  atk;
	int  def;
} Objetold;

//structure d'un personnage
typedef struct
{
	Pos   pos;
	int   pv;
	int   pv_max;
	int   atk;
	int   def;
	Objetold equip[5];
	char nom[VARCHAR];
	int  orientation;

} Persoold;

Pos get_pos (char *path);
Pos new_pos (int x, int y);
Objetold new_objet (char nom[], int id, int pv, int atk, int def);
Persoold new_perso (char nom[], Pos pos, int pv, int atk, int def);


#endif