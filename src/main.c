/** 
 * \file main.c 
 * Code principal.
*/

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include "io.h"

int main (int argc, char ** argv) {
	if (argc != 2)
	{
		printf("usage : ./bin/main ./grilles/<fichier grille>\n");
		return 1;
	}
	grille g, gc;
	init_grille_from_file (argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille (g, 0, 1, 0);
	debut_jeu (&g, &gc);
	libere_grille (&g);
	libere_grille (&gc);
	return 0;
}