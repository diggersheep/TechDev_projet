/**
* @file affichage.h
* @brief proto affichage
* @author Alexandre COMBEAU
* @date 13-04-2015
*/#ifndef __AFFICHAGE_H_
#define __AFFICHAGE_H_

#include "personnage.h"
#include "grille.h"

void  gestion_case   (Grille grid, int i, int j);
Persoold gesion         (Grille grid, int i, int j, Persoold perso, Objetold obj[], int taille_obj);
Persoold change_objet   (Persoold perso, Objetold old,Objetold new);
Persoold gestion_objet  (Grille grid, int n, int m, Persoold perso, Objetold obj[], int taille_obj);
void  obj2void       (Grille grid, int i, int j);
void  stats_perso    (Persoold perso);
Persoold afficher_perso (Grille grid, Persoold P, Objetold obj[], int taille_obj);
Persoold get_dep        (Grille grid, Persoold perso, Objetold obj[], int taille_obj);
void  perdu          (Grille grid, Persoold perso);
#endif