/**
* @file affichage.h
* @brief proto affichage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/
#ifndef __AFFICHAGE_H_
#define __AFFICHAGE_H_

#include "personnage.h"
#include "grille.h"

void  gestion_case   (Grille grid, int i, int j);
Perso gesion         (Grille grid, int i, int j, Perso perso, Objet obj[], int taille_obj);
Perso change_objet   (Perso perso, Objet old,Objet new);
Perso gestion_objet  (Grille grid, int n, int m, Perso perso, Objet obj[], int taille_obj);
void  obj2void       (Grille grid, int i, int j);
void  stats_perso    (Perso perso);
Perso afficher_perso (Grille grid, Perso P, Objet obj[], int taille_obj);
Perso get_dep        (Grille grid, Perso perso, Objet obj[], int taille_obj);
void  perdu          (Grille grid, Perso perso);
#endif