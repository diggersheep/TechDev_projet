/**
* @file SDL_affichage.c
* @brief affichage avec SDL
* @author Alexandre COMBEAU, Alain KABBOUH
* @date 01-05-2015
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "grille.h"
#include "SDL_affichage.h"
#include "objet.h"
#include "personnage.h"
#include "monstre.h"

#define MAX_SPRITE 2000


//=========================================
//    VARIABLES GLOBALES POUR SDL
//=========================================
SDL_Surface* screen = NULL;                 //context de la fenetre
SDL_Surface* fond_stats = NULL;
SDL_Surface* ATK = NULL;
SDL_Surface* DEF = NULL;
SDL_Surface* ATKOBJ = NULL;
SDL_Surface* DEFOBJ = NULL;
SDL_Surface* background_chargement = NULL;
SDL_Surface* background_pause = NULL;
SDL_Surface* pause_img = NULL;
SDL_Rect screen_position;                   //position dans la fenetre

unsigned int screen_size_l;                 //taille de la fenetre
unsigned int screen_size_h;                 //taille de la fenetre
unsigned int sceen_case_size = 32;          //taille d'une case en pixel

ObjScreen screen_image[MAX_SPRITE];         //banque d'image #hold-up X)
unsigned int screen_image_taille = 0;       //taille de la banque d'image
unsigned short chargement_pourcent = 0;     //indicateur barre de chargement

//=========================================


SDL_Surface* rechercheImg (id)
{
	unsigned int i;
	for (i = 0 ; i < screen_image_taille ; i++)
		if (screen_image[i].id == id)
			return screen_image[i].img;

	printf("ErreurRechercheImg : l'image n'a pas été trouvée - id:%d\n", id);
	exit(EXIT_FAILURE);
}

void initSDL (int l, int h)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_Quit();
		exit(EXIT_FAILURE); //#DESTRUCTION !!!!!!!!!
	}

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(l, h, 32, SDL_SWSURFACE);

	screen_size_l = l;
	screen_size_h = h;

	screen_position.x = 0 ;
	screen_position.y = 0 ;
}

void attendre_touche (void)
{
	SDL_Event e;

	do
		SDL_WaitEvent(&e);
	while (e.type != SDL_QUIT && e.type != SDL_KEYDOWN);
}

void afficher_case (SDL_Surface* img)
{
	SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format,0,0,0));
	SDL_BlitSurface(img, NULL, screen, &screen_position);
}

void SDL_AfficherGrille(grille g)
{
	if (g == NULL)
	{
		printf("ErreurSDL_AfficherGrille : La grille est vide (NULL) - (%p)\n", &g);
		exit(EXIT_FAILURE);
	}

	unsigned int i;
	unsigned int j;

	for (i = 0 ; i < g->n ; i++)
	{
		for (j = 0 ; j < g->m ; j++)
		{
			afficher_case(rechercheImg(g->grid[i][j]));

			if (screen_position.x == (screen_size_l - sceen_case_size))
			{
				screen_position.x  = 0;
				screen_position.y += sceen_case_size;
			}
			else
			{
				screen_position.x += sceen_case_size;
			}
		}
	}
}

void setImage (int id, char* path)
{
	if(screen_image_taille >= MAX_SPRITE)
		return;

	screen_image[screen_image_taille].img = SDL_LoadBMP(path);
	screen_image[screen_image_taille].id  = id;
	screen_image_taille++;
}


void chargement (int current, int max)
{
	SDL_Rect pos_charg;
	SDL_Surface* rect1 = NULL;
	SDL_Surface* rect2 = NULL;
	SDL_Surface* barre = NULL;

	pos_charg.x = (screen_size_l / 2) - (204 / 2);
	pos_charg.y = (screen_size_h / 2) - (54 / 2);

	rect1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 204, 54, 32, 0, 0, 0, 0);
	SDL_SetColorKey(rect1, SDL_SRCCOLORKEY, SDL_MapRGB(rect1->format,0,0,0));
	SDL_FillRect(rect1, NULL, SDL_MapRGB(rect1->format, 163, 178, 174));
	SDL_BlitSurface(rect1, NULL, screen, &pos_charg);


	pos_charg.x = (screen_size_l / 2) - (200 / 2);
	pos_charg.y = (screen_size_h / 2) - (50 / 2);


	rect2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 50, 32, 0, 0, 0, 0);
	SDL_SetColorKey(rect2, SDL_SRCCOLORKEY, SDL_MapRGB(rect2->format,0,0,0));
	SDL_FillRect(rect2, NULL, SDL_MapRGB(rect2->format, 17, 75, 66));
	SDL_BlitSurface(rect2, NULL, screen, &pos_charg); 

	chargement_pourcent = current*100 / max;

	pos_charg.x = 0;
	pos_charg.y = 0;


	pos_charg.x = (screen_size_l / 2) - 100;
	pos_charg.y = (screen_size_h / 2) - (50 / 2);

	barre = SDL_CreateRGBSurface(SDL_HWSURFACE, 2*chargement_pourcent, 50, 32, 0, 0, 0, 0);
	SDL_SetColorKey(barre, SDL_SRCCOLORKEY, SDL_MapRGB(barre->format,0,0,0));
	SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 76, 166, 142));
	SDL_BlitSurface(barre, NULL, screen, &pos_charg); 




	SDL_Flip(screen);
	SDL_FreeSurface(rect1);
	SDL_FreeSurface(rect2);
	SDL_FreeSurface(barre);

}

void setAllImage (void)
{
	int i;
	int j;
	int k;

	SDL_Rect pos_tmp;

	int max = 112 + 500 + 10;
	background_chargement = SDL_LoadBMP("ressources/img/background_chargement.bmp");
	pos_tmp.x = 0;
	pos_tmp.y = 0;

	SDL_SetColorKey(background_chargement, SDL_SRCCOLORKEY, SDL_MapRGB(background_chargement->format,0,0,0));
	SDL_BlitSurface(background_chargement, NULL, screen, &pos_tmp);

	chargement(0, max);
	setImage(0, "ressources/img/etoile.bmp");
	chargement(1, max);

	setImage(1, "ressources/img/mur.bmp");
	chargement(2, max);

	for (i = 0 ; i < 100 ; i++)
	{
		setImage(200 + i, "ressources/img/soin.bmp");
		chargement(3+i, max);
	}

	setImage(500,"ressources/img/sol.bmp");
	chargement(4+i, max);
	
	setImage(501,"ressources/img/sol2.bmp");
	chargement(5+i, max);
	
	setImage(502,"ressources/img/sol3.bmp");
	chargement(6+i, max);

	setImage(1000,"ressources/img/obj.bmp");
	chargement(7+i, max);

	setImage(510, "ressources/img/black_hole.bmp");
	chargement(8+i, max);

	for (j = 0 ; j < 499 ; j++) //Je comptais mettre plein de design différent, mais je n'ai pas eu le temps d'en faire plus ...
	{
		setImage(1001 + j, "ressources/img/obj.bmp");
		chargement(9+i+j, max);
	}

	fond_stats = SDL_LoadBMP("ressources/img/fond_stats.bmp");
	chargement(10+i+j, max);

	ATK = SDL_LoadBMP("ressources/img/atk.bmp");
	chargement(11+i+j, max);
	DEF = SDL_LoadBMP("ressources/img/def.bmp");
	chargement(12+i+j, max);
	ATKOBJ = SDL_LoadBMP("ressources/img/obj_atk.bmp");
	chargement(13+i+j, max);
	DEFOBJ = SDL_LoadBMP("ressources/img/obj_atk.bmp");
	chargement(14+i+j, max);

	for (k = 0 ; k < 10 ; k++)
	{
		setImage(100 + k, "ressources/img/piege1_10.bmp");
		chargement(15+i+j+k, max);
	}

	background_pause = SDL_LoadBMP("ressources/img/background.bmp");
	chargement(16+i+j+k, max);
}


void unsetImage (void)
{
	while(screen_image_taille != 0)
	{
		SDL_FreeSurface(screen_image[screen_image_taille].img);
		screen_image_taille--;
	}
	SDL_FreeSurface(fond_stats);
	SDL_FreeSurface(ATK);
	SDL_FreeSurface(DEF);
	SDL_FreeSurface(ATKOBJ);
	SDL_FreeSurface(DEFOBJ);
	SDL_FreeSurface(background_chargement);
	SDL_FreeSurface(background_pause);

	printf("Toutes les images ont été désalouées\n");
}



void afficherPerso (perso p)
{

	if (p == NULL)
	{
		printf("ErreurAfficherPerso : Le personnage n'existe pas (NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}
	SDL_Rect tmp = screen_position;
	
	screen_position.x = (p->pos.x)* sceen_case_size;
	screen_position.y = (p->pos.y)* sceen_case_size;

	afficher_case(p->img[p->orientation]);

	screen_position = tmp;
}

void afficherMob (void)
{
	//array_mob_screen_length
	//array_mob_screen
	unsigned int i;

	for ( i = 0 ; i < array_mob_screen_length ; i++ )
		afficherPerso(array_mob_screen[i].m);
}

void BarreDeVie (perso p)
{
	if (p == NULL)
	{
		printf("ErreurBarreDeVie : Le personnage est nul ... (=NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	SDL_Rect pos_vie;
	SDL_Surface* rect1 = NULL;
	SDL_Surface* rect2 = NULL;
	SDL_Surface* barre = NULL;
	float pv = p->pv / (float)p->pv_max;
	int barre_vie = pv * 312;

	if (barre_vie < 0)
		barre_vie = 0;

	pos_vie.x = 2;
	pos_vie.y = screen_size_h - sceen_case_size*5 + 16;

	rect1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 316, 32, 32, 0, 0, 0, 0);
	SDL_FillRect(rect1, NULL, SDL_MapRGB(rect1->format, 64, 64, 64));
	SDL_BlitSurface(rect1, NULL, screen, &pos_vie);


	pos_vie.x += 2;
	pos_vie.y += 2;


	rect2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 312, 28, 32, 0, 0, 0, 0);
	SDL_FillRect(rect2, NULL, SDL_MapRGB(rect2->format, 133, 6, 6));
	SDL_BlitSurface(rect2, NULL, screen, &pos_vie); 

	

	barre = SDL_CreateRGBSurface(SDL_HWSURFACE, barre_vie , 28 , 32, 0, 0, 0, 0);
	SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 255, 9, 33));
	SDL_BlitSurface(barre, NULL, screen, &pos_vie); 

	
	SDL_FreeSurface(rect1);
	SDL_FreeSurface(rect2);
	SDL_FreeSurface(barre);
}


void FondStatsPerso (void)
{
	SDL_Rect pos_fond;

	pos_fond.x = 0;
	pos_fond.y = screen_size_h - sceen_case_size*5;

	SDL_BlitSurface(fond_stats, NULL, screen, &pos_fond);
}

void afficherStatsATK (perso p)
{
	if (p == NULL)
	{
		printf("ErreurBarreDeVie : Le personnage est nul ... (=NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	SDL_Rect pos_atk;
	SDL_Surface* rect1 = NULL;
	SDL_Surface* rect2 = NULL;
	SDL_Surface* barre = NULL;
	float atk = p->atk / 50.0;
	int barre_atk = atk * 236;


	pos_atk.x = 0;
	pos_atk.y = screen_size_h - sceen_case_size*5 + 16 + 32 + 16;


	SDL_SetColorKey(ATK, SDL_SRCCOLORKEY, SDL_MapRGB(ATK->format,0,0,0));
	SDL_BlitSurface(ATK, NULL, screen, &pos_atk);

	pos_atk.x += 64;

	rect1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 240, 32, 32, 0, 0, 0, 0);
	SDL_FillRect(rect1, NULL, SDL_MapRGB(rect1->format, 64, 64, 64));
	SDL_BlitSurface(rect1, NULL, screen, &pos_atk);


	pos_atk.x += 2;
	pos_atk.y += 2;


	rect2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 236, 28, 32, 0, 0, 0, 0);
	SDL_FillRect(rect2, NULL, SDL_MapRGB(rect2->format, 127, 154, 101));
	SDL_BlitSurface(rect2, NULL, screen, &pos_atk); 

	

	barre = SDL_CreateRGBSurface(SDL_HWSURFACE, barre_atk , 28 , 32, 0, 0, 0, 0);
	SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 102, 205, 0));
	SDL_BlitSurface(barre, NULL, screen, &pos_atk); 

	
	SDL_FreeSurface(rect1);
	SDL_FreeSurface(rect2);
	SDL_FreeSurface(barre);
}
void afficherStatsDEF (perso p)
{
	if (p == NULL)
	{
		printf("ErreurBarreDeVie : Le personnage est nul ... (=NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	SDL_Rect pos_def;
	SDL_Surface* rect1 = NULL;
	SDL_Surface* rect2 = NULL;
	SDL_Surface* barre = NULL;
	float def = p->def / 50.0;
	int barre_def = def * 236;


	pos_def.x = 0;
	pos_def.y = screen_size_h - sceen_case_size*5 + 16 + 32 + 16 + 16 + 32;


	SDL_SetColorKey(DEF, SDL_SRCCOLORKEY, SDL_MapRGB(DEF->format,0,0,0));
	SDL_BlitSurface(DEF, NULL, screen, &pos_def);

	pos_def.x += 64;

	rect1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 240, 32, 32, 0, 0, 0, 0);
	SDL_FillRect(rect1, NULL, SDL_MapRGB(rect1->format, 64, 64, 64));
	SDL_BlitSurface(rect1, NULL, screen, &pos_def);


	pos_def.x += 2;
	pos_def.y += 2;


	rect2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 236, 28, 32, 0, 0, 0, 0);
	SDL_FillRect(rect2, NULL, SDL_MapRGB(rect2->format, 82, 139, 139));
	SDL_BlitSurface(rect2, NULL, screen, &pos_def);

	

	barre = SDL_CreateRGBSurface(SDL_HWSURFACE, barre_def , 28 , 32, 0, 0, 0, 0);
	SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 121, 205, 205));
	SDL_BlitSurface(barre, NULL, screen, &pos_def); 

	
	SDL_FreeSurface(rect1);
	SDL_FreeSurface(rect2);
	SDL_FreeSurface(barre);
}	

void afficherObjet(perso p, int emplacement)
{
	if (p == NULL)
	{
		printf("ErreurAfficherObjet : Le personnage est nul ... (=NULL) - (%p)\n", &p);
		exit(EXIT_FAILURE);
	}

	SDL_Rect pos_obj;

	SDL_Surface* rect11 = NULL;
	SDL_Surface* rect21 = NULL;
	SDL_Surface* barre1 = NULL;
	SDL_Surface* rect12 = NULL;
	SDL_Surface* rect22 = NULL;
	SDL_Surface* barre2 = NULL;
	SDL_Surface* rect13 = NULL;
	SDL_Surface* rect23 = NULL;
	SDL_Surface* barre3 = NULL;
	SDL_Surface* tmp    = NULL;
	float pv  = p->equip[emplacement].pv  / (float)30.0;
	float atk = p->equip[emplacement].atk / (float)30.0;
	float def = p->equip[emplacement].def / (float)30.0;

	//printf("================> %d:%d:%d\n",  p->equip[emplacement].pv ,  p->equip[emplacement].atk,  p->equip[emplacement].def);

	pos_obj.x = 320;
	pos_obj.y = screen_size_h - sceen_case_size * (5 - emplacement);



	tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 32, 0, 0, 0, 0);
	SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, 64, 64, 64));
	SDL_BlitSurface(tmp, NULL, screen, &pos_obj);

	SDL_SetColorKey(p->equip[emplacement].img, SDL_SRCCOLORKEY, SDL_MapRGB(p->equip[emplacement].img->format,0,0,0));
	SDL_BlitSurface(p->equip[emplacement].img, NULL, screen, &pos_obj);

	pos_obj.x += 32 + 4 ;
	pos_obj.y += 8;


	rect11 = SDL_CreateRGBSurface(SDL_HWSURFACE, 90, 16, 32, 0, 0, 0, 0);
	SDL_FillRect(rect11, NULL, SDL_MapRGB(rect11->format, 64, 64, 64));
	SDL_BlitSurface(rect11, NULL, screen, &pos_obj);

	pos_obj.x += 2;
	pos_obj.y += 2;

	rect21 = SDL_CreateRGBSurface(SDL_HWSURFACE, 86, 12, 32, 0, 0, 0, 0);
	SDL_FillRect(rect21, NULL, SDL_MapRGB(rect21->format, 133, 6, 6));
	SDL_BlitSurface(rect21, NULL, screen, &pos_obj);

	barre1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 86 * atk, 12, 32, 0, 0, 0, 0);
	SDL_FillRect(barre1, NULL, SDL_MapRGB(barre1->format, 255, 9, 33));
	SDL_BlitSurface(barre1, NULL, screen, &pos_obj);

	pos_obj.x += 96 - 3 - 2;
	pos_obj.y += -2;




	rect12 = SDL_CreateRGBSurface(SDL_HWSURFACE, 90, 16, 32, 0, 0, 0, 0);
	SDL_FillRect(rect12, NULL, SDL_MapRGB(rect12->format, 64, 64, 64));
	SDL_BlitSurface(rect12, NULL, screen, &pos_obj);

	pos_obj.x += 2;
	pos_obj.y += 2;

	rect22 = SDL_CreateRGBSurface(SDL_HWSURFACE, 86, 12, 32, 0, 0, 0, 0);
	SDL_FillRect(rect22, NULL, SDL_MapRGB(rect22->format, 127, 154, 101));
	SDL_BlitSurface(rect22, NULL, screen, &pos_obj);

	barre2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 86 * atk, 12, 32, 0, 0, 0, 0);
	SDL_FillRect(barre2, NULL, SDL_MapRGB(barre2->format, 102, 205, 0));
	SDL_BlitSurface(barre2, NULL, screen, &pos_obj);





	pos_obj.x += 96 - 3 - 2;
	pos_obj.y += -2;

	rect13 = SDL_CreateRGBSurface(SDL_HWSURFACE, 90, 16, 32, 0, 0, 0, 0);
	SDL_FillRect(rect13, NULL, SDL_MapRGB(rect13->format, 64, 64, 64));
	SDL_BlitSurface(rect13, NULL, screen, &pos_obj);

	pos_obj.x += 2;
	pos_obj.y += 2;

	rect23 = SDL_CreateRGBSurface(SDL_HWSURFACE, 86, 12, 32, 0, 0, 0, 0);
	SDL_FillRect(rect23, NULL, SDL_MapRGB(rect23->format, 82, 139, 139));
	SDL_BlitSurface(rect23, NULL, screen, &pos_obj);


	barre3 = SDL_CreateRGBSurface(SDL_HWSURFACE, 86 * def, 12, 32, 0, 0, 0, 0);
	SDL_FillRect(barre3, NULL, SDL_MapRGB(barre3->format, 121, 205, 205));
	SDL_BlitSurface(barre3, NULL, screen, &pos_obj);


	SDL_FreeSurface(rect11);
	SDL_FreeSurface(rect21);
	SDL_FreeSurface(barre1);
	SDL_FreeSurface(rect12);
	SDL_FreeSurface(rect22);
	SDL_FreeSurface(barre2);
	SDL_FreeSurface(rect13);
	SDL_FreeSurface(rect23);
	SDL_FreeSurface(barre3);
	SDL_FreeSurface(tmp);
}

void afficherStats (perso p)
{
	FondStatsPerso();
	BarreDeVie(p);
	afficherStatsATK(p);
	afficherStatsDEF(p);
	afficherObjet(p, 0);
	afficherObjet(p, 1);
	afficherObjet(p, 2);
	afficherObjet(p, 3);
	afficherObjet(p, 4);
}

void afficherPause (void)
{
	SDL_Rect tmp;
	tmp.x = 0;
	tmp.y = 0;
	
	SDL_BlitSurface(background_pause, NULL, screen, &tmp);
}