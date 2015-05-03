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

void  gestion_case   (grille grid, int i, int j);
Perso gesion         (grille grid, int i, int j, Perso perso, Objet obj[], int taille_obj);
Perso change_objet   (Perso perso, Objet old,Objet new);
Perso gestion_objet  (grille grid, int n, int m, Perso perso, Objet obj[], int taille_obj);
void  obj2void       (grille grid, int i, int j);
void  stats_perso    (Perso perso);
Perso afficher_perso (grille grid, Perso P, Objet obj[], int taille_obj);
Perso get_dep        (grille grid, Perso perso, Objet obj[], int taille_obj);
void  perdu          (grille grid, Perso perso);
#endif