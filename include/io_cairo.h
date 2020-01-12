/**
 * \file io_cairo.h
 * Définition des fonctions \n
 * affiche_grille_cairo et debut_jeu_cairo. \n
*/

/**
 * \def __IO_CAIRO_H__
*/
#ifndef __IO_CAIRO_H__
#define __IO_CAIRO_H__

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "grille.h"
#include "jeu.h"

#define SIZEX 550
#define SIZEY 550
#define SIZECELL 40
#define INITX 25
#define INITY 100

void affiche_grille_cairo (cairo_surface_t *surface ,grille g);
void debut_jeu_cairo (grille *g, grille *gc);

#endif
