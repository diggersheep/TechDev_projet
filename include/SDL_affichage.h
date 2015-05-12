/**
* @file SDL_affichage.h
* @brief proto affichage avec SDL
* @author Alexandre COMBEAU
* @date 01-05-2015
*/
#ifndef __SDL_AFFICHAGE_H_
#define __SDL_AFFICHAGE_H_


#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "grille.h"
#include "SDL_affichage.h"
#include "personnage.h"

#define MAX_SPRITE 2000

/**Strucure associative : id / image.
	Utile pour gérer efficacement les sprites*/
typedef struct StrObjScreen
{
	int id;
	SDL_Surface* img;
} ObjScreen;

//=========================================
//    VARIABLES GLOBALES POUR SDL
//=========================================
#define MAX_SPRITE 2000
SDL_Surface* screen;               //context de la fenetre
SDL_Surface* fond_stats;
SDL_Surface* ATKOBJ;
SDL_Surface* DEFOBJ;
SDL_Surface* background_chargement;
SDL_Surface* background_pause;
SDL_Surface* pause_img;
SDL_Rect screen_position;                 //position dans la fenetre

unsigned int screen_size_l;               //taille de la fenetre
unsigned int screen_size_h;               //taille de la fenetre
unsigned int sceen_case_size;        //taille d'une case en pixel

ObjScreen screen_image[MAX_SPRITE];       //banque d'image #hold-up X)
unsigned int screen_image_taille;     //taille de la banque d'image
unsigned short chargemement_pourcent; //indicateur barre de chargement
//=========================================


/**Initialise SDL avec une lageur et une hauteur donnée*/
void initSDL (int l, int h);
/**Equivalent de Pause/Wait*/
void attendre_touche (void);
/**Affiche sur la fenetre une image avec par défaut la transpence règlée sur NOIR(0,0,0)*/
void afficher_case (SDL_Surface* img);
/**stock une image*/
void setImage (int id, char* path);
/**Petit écran de chargement :D */
void chargement (int current, int max);
/**Charge les sprite*/
void setAllImage (void);
/**Désaloue les images stockés dans la variable screen_image*/
void unsetImage (void);
/**Affiche une grille avec SDL*/
void SDL_AfficherGrille(grille g);
/**Affiche un personnage (joueur ou monstre)*/
void afficherPerso (perso p);

//=================================
//    Interface de stats
//=================================
/**Affichage de la barre de vie du joueur*/
void BarreDeVie (perso p);
/**Affichage du fond sur lequel les stats vont s'afficher*/
void FondStatsPerso (void);
#endif