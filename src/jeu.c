/**
 * \file jeu.c
 * Implémentation des fonctions compte_voisins_vivants, \n
 * compte_voisins_vivants_cyclique, compte_voisins_vivants_noncyclique, \n
 * vieillissement, evolution, evolue et evolue_vieillissement. \n
*/

#include "jeu.h"

/**
 * \fn int (*compte_voisins_vivants) (int i, int j, grille g);
 * \brief Pointe vers une des deux fonctions de comptage des voisins (cyclique ou non-cyclique)
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
 * \return entier (resultat des fonctions pointées)
*/ 
int (*compte_voisins_vivants) (int i, int j, grille g);

/**
 * \fn int compte_voisins_vivants_cyclique (int i, int j, grille g);
 * \brief Compte le nombre de voisins vivants de la cellule (i,j) de façon cyclique
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
 * \return entier (resultat du comptage)
*/
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 * \fn int compte_voisins_vivants_noncyclique (int i, int j, grille g);
 * \brief Compte le nombre de voisins vivants de la cellule (i,j) de façon non-cyclique
 * \relatesalso grille
 * \param i entier (numero de ligne)
 * \param j entier (numero de colonne)
 * \param g grille (nom de la grille)
 * \return entier (resultat du comptage)
*/
int compte_voisins_vivants_noncyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	if (i>0 && j>0) 	v+= est_vivante(i-1,j-1,g);
	if (i>0) 			v+= est_vivante(i-1,j,g);
	if (i>0 && j<c-1) 	v+= est_vivante(i-1,j+1,g);
	if (j>0) 			v+= est_vivante(i,j-1,g);
	if (j<c-1) 			v+= est_vivante(i,j+1,g);
	if (i<l-1 && j>0)	v+= est_vivante(i+1,j-1,g);
	if (i<l-1) 			v+= est_vivante(i+1,j,g);
	if (i<l-1 && j<c-1)	v+= est_vivante(i+1,j+1,g);

	return v; 
}

/**
 * \fn void vieillissement(int i, int j, grille g);
 * \brief Effectue le vieillissement des cellules  et vérifie si la cellule est viable
 * \relatesalso grille
 * \param l entier (numero de ligne)
 * \param c entier (numero de colonne)
 * \param g pointeur sur grille (nom de la grille)
*/ 
void vieillissement(int l, int c, grille g){
    if(!(est_non_viable(l,c,g)) && g.cellules[l][c]<=8) g.cellules[l][c]++;
    else set_morte(l, c, g);
}

/**
 * \fn void (*evolution) (grille *g, grille *gc);
 * \brief Pointe vers une des deux fonctions de l'evolution des cellules
 * \relatesalso grille
 * \param g pointeur sur grille (grille source)
 * \param gc pointeur sur grille (grille copiée)
*/
void (*evolution) (grille *g, grille *gc);

/**
 * \fn void evolue (grille *g, grille *gc);
 * \brief Fait évoluer la grille g d'un pas de temps
 * \relatesalso grille
 * \param g pointeur sur grille (grille source)
 * \param gc pointeur sur grille (grille copiée)
*/
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j) 
		{
			v = (*compte_voisins_vivants) (i, j, *gc);
			if(!(est_non_viable(i, j, *g)))
			{ //verifie si la cellule est viable sinon passe à la cellule suivante
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}

/**
 * \fn void evolue_vieillisement (grille *g, grille *gc);
 * \brief Fait évoluer la grilles en faisant mourir ou naitre des cellules selon leur voisinage et selon leur age (si elles sont à plus de 8 étapes elles meurent)
 * \relatesalso grille
 * \param g pointeur sur grille (grille source)
 * \param gc pointeur sur grille (grille copiée)
*/
void evolue_vieillissement (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (*compte_voisins_vivants) (i, j, *gc);
			if(!(est_non_viable(i, j, *g)))
			{ //verifie si la cellule est viable sinon passe à la cellule suivante
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					vieillissement(i, j, *g);
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);	
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}

/**
 * \fn int oscillante (grille g);
 * \brief teste si une grille est morte ou oscillante
 * \relatesalso grille
 * \param g grille
 * \return entier
*/
int oscillante (grille g){
	int cpt = 0 ;
	grille g1,g2 ;
	alloue_grille(g.nbl,g.nbc,&g1) ;
	copie_grille(g,g1);
	alloue_grille(g.nbl,g.nbc,&g2) ;
	for(int j=1; j <= 50 && cpt == 0; j++){
		evolue(&g1,&g2) ;
		if(grilles_identiques(&g,&g1) == 1) cpt = j ;
	}
	if(grille_morte(&g) == 1 ) cpt = -1 ;
	libere_grille(&g1);
	libere_grille(&g2);
	return cpt;
}
