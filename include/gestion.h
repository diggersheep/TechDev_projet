#ifndef __GESTION_H_
#define __GESTION_H_

#include "objet.h"
#include "personnage.h"

/**
* @file gestion.c
* @brief sources contenant les fonctions objet
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 03-05-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "grille.h"
#include "objet.h"
#include "personnage.h"

typedef int bool;

//TEMPORAIRE
void gameover (perso p, grille g);

/**Echange deux objets si possible*/
void echangeObjet (Objet obj, int i, perso p);
/**Vérifie si l'objet par terre est plus intéressant que celui possèdé*/
void checkObjet(int id, int i, perso p);
/*Gestion de tous les objets*/
void gestionObjet(int id, perso p, grille g);
/**Fonction qui calcul les dégâts subit avec la formule : degat = ATK(attanquant) - ( DEF(attaqué) / 5)*/
int  degat (int atk, int def);
/**Fonction qui calcul les points de vie rendu avec la formule : PV_rendu = soin + (soin * def(perso)) / 100 */
int soin (int heal, int def);
/**Fonction qui change les pv d'un personnage*/
void changePV (perso p, int x);
/**Fonction booléenne qui renvoie 1 s'il y a collision, et 0 sinon*/
int  gestionCollision (int id);
/**Fonction de gestion des pièges*/
void gestionPiege (perso p, int id);
/**Fonction de gestion des soins*/
void gestionSoin (perso p, int id);
/**Booléen qui check si un personnage est mort ou pas*/
bool mort (perso p);
/**Fonction qui définie la fin de la vie d'un personnage en fonction de son type, soit un joueur, soit un monstre*/
void gestionVie (perso p, grille g, int type);
/**Fonction générale qui regroupe toutes les fonctions de gestion en une seule*/
void gestion (grille g, perso p, int id, int type);

#endif