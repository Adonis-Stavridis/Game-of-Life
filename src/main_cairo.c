/**
 * \file main_cairo.c
 * Code principal.
*/

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include "io_cairo.h"

int main (int argc, char *argv[]){
	if (argc != 2)
	{
		printf("usage : ./bin/main ./grilles/<grille_number.txt>\n");
		return 1;
	}
	grille g, gc;
	init_grille_from_file (argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	debut_jeu_cairo (&g, &gc);
	libere_grille (&g);
	libere_grille (&gc);
	return 0;
}
