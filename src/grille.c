/**
 * \file grille.c
 * Implémentation des fonctions aloue_grille, \n
 * libere_grille, init_grille_from_file et copie_grille. \n
*/

#include "grille.h"

/**
 * \fn void alloue_grille (int l, int c, grille* g);
 * \brief Alloue une grille de la taille l*c et initialise ses cellules a mortes
 * \relatesalso grille
 * \param l entier (numero de ligne)
 * \param c entier (numero de colonne)
 * \param g pointeur sur grille (nom de la grille)
*/
void alloue_grille (int l, int c, grille *g){
	g -> nbl = l;
	g -> nbc = c;
	g -> cellules = (int**) malloc (l * sizeof (int*));
	for (int i = 0; i < l; i++){
		g -> cellules[i] = (int*) calloc (c, sizeof (int));
	}
}

/**
 * \fn void libere_grille (grille* g);
 * \brief Libere la grille
 * \relatesalso grille
 * \param g pointeur sur grille (nom de la grille)
*/
void libere_grille (grille *g){
	for (int i = 0; i < (g -> nbl); i++){
		free (g -> cellules[i]);
	}
	free (g -> cellules);
}

/**
 * \fn void init_grille_from_file (char* filename, grille* g);
 * \brief Ouvre une grille depuis un fichier
 * \relatesalso grille
 * \param filename pointeur sur caractère (nom d'un fichier)
 * \param g pointeur sur grille (nom de la grille)
*/
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0, non_viable=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);//lit les cellules vivantes
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile,"%d", & non_viable);//lit les cellules non viables
	for(n=0; n < non_viable; n++){
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_non_viable(i, j, *g);
	}
	
	fclose (pfile);
	return;
}

/**
 * \fn void copie_grille (grille gs, grille gd);
 * \brief Recopie gs dans gd (sans allocation)
 * \relatesalso grille
 * \param gs grille (grille source)
 * \param gd grille (grille copiée)
*/
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/**
 * \fn int grille_morte (grille g);
 * \brief teste si la grille est morte
 * \relatesalso grille
 * \param g grille
 * \return entier (booléen de l'opération)
*/ 
int grille_morte (grille* g){
	int b = 1;
	for (int i = 0; i<g->nbl && b == 1; i++){
		for (int j = 0; j<g->nbc && b == 1; j++){
			if (est_vivante(i,j,*g)) b = 0;
		}
	}
	return b;
}

/**
 * \fn int grilles_identiques (grille gs, grille gd);
 * \brief teste si les deux grilles sont identiques
 * \relatesalso grille
 * \param gs grille 1
 * \param gd grille 2
 * \return entier (booléen de l'opération)
*/
int grilles_identiques (grille* gs, grille* gd){
	int b = 1;
	for (int i = 0; i<gs->nbl && b == 1; i++){
		for (int j = 0; j<gs->nbc && b == 1; j++){
			if (gs->cellules[i][j] != gd->cellules[i][j]) b = 0;
		}
	}
	return b;
}
