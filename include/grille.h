/**
 * \file grille.h
 * Définition de la structure grille et \n
 * des fonctions alloue_grille, libere_grille, init_grille_from_file, \n
 * set_vivante, set_morte, est_vivante et copie_grille. \n
*/

/**
 * \def __GRILLE_H__
*/
#ifndef __GRILLE_H__
#define __GRILLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
/**
 * \typedef typedef struct grille
 * \brief Déclaration de la structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 * \param nbl entier (nombre de lignes)
 * \param nbc entier (nombre de colonnes)
 * \param cellules entier (cellule d'un tableau de tableau)
*/
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char* filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
 * \fn void set_vivante (int i, int j, grille g);
 * \brief Rend vivante la cellule (i,j) de la grille g
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
*/
static inline void set_vivante (int i, int j, grille g) {g.cellules[i][j] = 1;}

// rend morte la cellule (i,j) de la grille g
/**
 * \fn void set_morte (int i, int j, grille g);
 * \brief Rend morte la cellule (i,j) de la grille g
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
*/
static inline void set_morte (int i, int j, grille g) {g.cellules[i][j] = 0;}

// rend non viable la cellule(i,j) de la grille g
/**
 * \fn void set_non_viable(int i, int j, grille g);
 * \brief rend non-viable la cellule (i,j) de la grille g
 * \param i entier (lenumero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
*/
static inline void set_non_viable(int i, int j, grille g) {g.cellules[i][j] = -1;}

// teste si la cellule (i,j) de la grille g est vivante
/**
 * \fn int est_vivante (int i, int j, grille g);
 * \brief Teste si la cellule (i,j) de la grille g est vivante
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
 * \return entier (booléen du test)
*/
static inline int est_vivante (int i, int j, grille g) {return g.cellules[i][j] != 0;}


// teste si la cellule (i,j) de la grille g est non_viable
/**
 * \fn int est_non_viable(int i, int j, grille g);
 * \brief teste si la cellule (i,j) de la grille g est non_viable
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
 * \return entier (booléen du test)
*/
static inline int est_non_viable(int i, int j, grille g) {return (g.cellules[i][j] == -1);}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

// teste si la grille est morte
int grille_morte (grille* g);

// teste si les deux grilles sont identiques
int grilles_identiques (grille* gs, grille* gd);

#endif
