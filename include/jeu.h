/**
 * \file jeu.h
 * Définition des fonctions modulo, compte_voisins_vivants, \n
 * compte_voisins_vivants_cyclique, compte_voisins_vivants_noncyclique, \n
 * vieillissement, evolution, evolue et evolue_vieillissement. \n
*/

/**
 * \def __JEU_H__
*/
#ifndef __JEU_H__
#define __JEU_H__

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
 * \fn int modulo (int i, int m);
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * \param i entier
 * \param m entier
 * \return entier ((i+m)%m)
*/
static inline int modulo (int i, int m) {return (i+m)%m;}

// pointe vers une des deux fonctions de comptage des voisins (cyclique ou non-cyclique)
int (*compte_voisins_vivants) (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j) de façon cyclique
int compte_voisins_vivants_cyclique (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j) de façon non-cyclique
int compte_voisins_vivants_noncyclique (int i, int j, grille g);

// effectue le vieillissement des cellules
void viellissement (int l, int c, grille g);

// pointe vers une des deux fonctions de l'evolution des cellules
void (*evolution) (grille *g, grille *gc);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

// fait évoluer la grilles en faisant mourir ou naitre des cellules
// selon leur voisinage et selon leur age (si elles sont à plus de 8 étapes elles meurent)
void evolue_vieillissement (grille *g, grille *gc);

//teste si une grille est morte ou oscillante
int oscillante (grille g);

#endif
