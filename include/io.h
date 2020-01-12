/**
 * \file io.h
 * Définition des fonctions affiche_trait, affiche_ligne, \n
 * affiche_grille, efface_grille et debut_jeu. \n
*/

/**
 * \def __IO_H__
*/
#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g, int cpt, int b, int v);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
