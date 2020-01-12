/**
 * \file io.c
 * Implémentation des fonctions affiche_trait, affiche_ligne, \n
 * affiche_grille, efface_grille et debut_jeu. \n
*/

#include "io.h"

/**
 * \fn void affiche_trait (int c);
 * \brief Affichage d'un trait horizontal
 * \param c entier (nombre de colonnes)
*/
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * \fn void affiche_ligne (int c, int* ligne);
 * \brief Affichage d'une ligne de la grille
 * \param c entier (nombre de colonnes)
 * \param ligne pointeur sur entier (ligne correspondant à un tableau d'un tableau)
*/
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) {
		if (ligne[i] == 0 ) printf ("|   ");
		else if(ligne[i] > 0) printf ("| O ");
		else printf ("| X ");
	}
	printf("|\n");
	return;
}

/**
 * \fn void affiche_grille (grille g, int cpt, int b);
 * \brief Affichage d'une grille
 * \relatesalso grille
 * \param g grille (nom e la grille)
 * \param cpt entier (compteur permettant d'afficher le temps d'evolution)
 * \param b entier (booléen permettant d'afficher le calcul utilisé pour le voisinage)
 * \param v entier (booléen indiquant si le vieillissement est activé ou non)
*/
void affiche_grille (grille g, int cpt, int b, int v){
	int i, l=g.nbl, c=g.nbc;
	printf("\nEvolution: %d | Cyclic(1)/Not-cyclic(0): %d | Aging(1:Active/0:Not-active): %d\n\n",cpt,b,v);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

/**
 * \fn void efface_grille (grille g);
 * \brief Effacement d'une grille
 * \relatesalso grille
 * \param g grille (nom de la grille)
*/
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl * 2 + 7);
}

/**
 * \fn void debut_jeu(grille *g, grille *gc);
 * \brief Debute le jeu
 * \relatesalso grille
 * \param g pointeur sur grille (grille source)
 * \param gc pointeur sur grille (grille copiée)
*/
void debut_jeu (grille *g, grille *gc){
	int cpt = 0; //initialisation d'un compteur pour le temps d'evolution
	compte_voisins_vivants = compte_voisins_vivants_cyclique;
	evolution = evolue_vieillissement;
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolution(g,gc);
				efface_grille(*g);
				affiche_grille(*g, ++cpt,
					compte_voisins_vivants == compte_voisins_vivants_cyclique,
					evolution == evolue_vieillissement);
				break;
			}
			case 'n':
			{ // touche 'n' pour changer de grille
				char filename[25];
				printf("Choose the name of your grid: ");
				scanf("%s",filename);
				getchar();
				for (int i=0; i < ((g->nbl) * 2 + 7); i++) printf("\003[A\33[2K\r");
				libere_grille(g);
				init_grille_from_file(filename, g);
				alloue_grille(g -> nbl, g -> nbc, gc);
				affiche_grille(*g, cpt=0, compte_voisins_vivants == compte_voisins_vivants_cyclique, evolution==evolue_vieillissement);
				break;
			}
			case 'c':
			{ // touche 'c' pour changer de méthode de calcul du voisinage
				if (compte_voisins_vivants == compte_voisins_vivants_cyclique)
				compte_voisins_vivants = compte_voisins_vivants_noncyclique;
				else
				compte_voisins_vivants = compte_voisins_vivants_cyclique;
				break;
			}
			case 'v':
			{ // touche 'v' pour activer/désactiver le vieillissement des cellules
				if (evolution == evolue)
				evolution = evolue_vieillissement;
				else
				evolution = evolue;
				break;
			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}
