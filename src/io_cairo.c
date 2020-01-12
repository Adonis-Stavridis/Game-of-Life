/**
 * \file io_cairo.c
 * Implémentation des fonctions \n
 * affiche_grille_cairo et debut_jeu_cairo. \n
*/

#include "io_cairo.h"

void affiche_grille_cairo (cairo_surface_t *surface ,grille g)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.75, 0.75, 0.75);
	cairo_paint(cr);

	// lines
	int l = g.nbl ;
	int c = g.nbc ;
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	for (int n = 0 ; n <= l ; n++)
	{
		cairo_move_to (cr, INITX, INITY+(n*SIZECELL));
		cairo_line_to(cr, INITX+(c*SIZECELL),INITY+(n*SIZECELL));
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	}
	for (int n = 0 ; n <= c ; n++)
	{
		cairo_move_to (cr, INITX+(n*SIZECELL), INITY);
		cairo_line_to(cr, INITX+(n*SIZECELL),INITY+(l*SIZECELL));
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	}
	//cellules
	for (int i = 0 ; i < l ; i++)
	for (int j = 0 ; j < c ; j++)
	{
		if (g.cellules[i][j] == -1)
		{
			cairo_rectangle(cr,INITX+(j*SIZECELL)+1,INITY+(i*SIZECELL)+1,SIZECELL-2,SIZECELL-2);
			cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
			cairo_fill(cr);
		}
		else if (est_vivante(i,j,g))
		{
			cairo_rectangle(cr,INITX+(j*SIZECELL)+1,INITY+(i*SIZECELL)+1,SIZECELL-2,SIZECELL-2);
			cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
			cairo_fill(cr);
		}
	}
	cairo_destroy(cr);
}

void debut_jeu_cairo(grille *g, grille *gc)
{
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	int q = 0 ;
	int i = 0 ;
	char str[12];
	KeySym key ;
	char keybuf[8] ;
	//char ch ;
	compte_voisins_vivants = compte_voisins_vivants_cyclique;
	evolution = evolue_vieillissement;

	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Game of Life");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cairo_surface_t *cs;
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);
	// run the event loop
	while(q == 0)
	{
		sprintf(str, "%d", i);
		affiche_grille_cairo(cs,*g);
    	cairo_t *cr = cairo_create(cs);
    	cairo_select_font_face (cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
		cairo_set_font_size (cr, 14);
		cairo_set_source_rgb (cr, 0.25, 0.25, 0.25);
		cairo_move_to (cr, 60, 40);
		cairo_show_text (cr, "Evolution: ");
		cairo_show_text (cr, str);
		cairo_show_text (cr, " | Cyclic: ");
		(compte_voisins_vivants == compte_voisins_vivants_cyclique ?
			cairo_show_text(cr,"Yes") : cairo_show_text(cr,"No"));
		cairo_show_text (cr, " | Aging: ");
		(evolution == evolue ?
			cairo_show_text(cr,"Yes") : cairo_show_text(cr,"No"));
    	cairo_destroy(cr);
		XNextEvent(dpy, &e);
		switch(e.type)
		{
			case ButtonPress:
			{
				switch(e.xbutton.button)
				{
					case Button1:
					{
						evolue(g,gc);
						i++;
						break;
					}
					case Button3:
					{
						q=1;
						break;
					}
				}
				break;
			}
			case KeyPress:
			{
				XLookupString(&e.xkey, keybuf, sizeof(keybuf), &key, NULL) ;
				switch(key)
				{
					case 'c':
					{//c
						if (compte_voisins_vivants == compte_voisins_vivants_cyclique)
						compte_voisins_vivants = compte_voisins_vivants_noncyclique;
						else
						compte_voisins_vivants = compte_voisins_vivants_cyclique;
						break;
					}
					case 'v':
					{//v
						if (evolution == evolue)
						evolution = evolue_vieillissement;
						else
						evolution = evolue;
						break;
					}
					case 'n':
					{
						cairo_t *cr = cairo_create(cs);
						cairo_select_font_face (cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
						cairo_set_font_size (cr, 14);
						cairo_set_source_rgb (cr, 0.25, 0.25, 0.25);
						cairo_move_to (cr, 60, 70);
						cairo_show_text (cr, "--Enter grid name in the terminal--");
						cairo_destroy(cr);
						XNextEvent(dpy, &e);
						char filename[25];
						printf("Choose the name of your grid: ");
						scanf("%s",filename);
						getchar();
						printf("\003[A\33[2K\r");
						libere_grille(g);
						init_grille_from_file(filename, g);
						libere_grille(gc);
						alloue_grille(g -> nbl, g -> nbc, gc);
						i = 0;
						break;
					}
					case 'o':
					{//o
						cairo_t *cr = cairo_create(cs);
   				 		cairo_select_font_face (cr, "monospace", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
						cairo_set_font_size (cr, 14);
						cairo_set_source_rgb (cr, 0.25, 0.25, 0.25);
    					cairo_move_to (cr, 60, 70);
						int cpt = oscillante(*g) ;
						switch(cpt)
						{
							case -1:
							{
								cairo_show_text (cr, "The grid is empty");
								break;
							}
							case 0:
							{
								cairo_show_text (cr, "The grid isn't oscillanting");
								break;
							}
							case 1:
							{
								cairo_show_text (cr, "The grid is static");
								break;
							}
							default:
							{
								cairo_show_text (cr, "The grid is oscillanting of period: ");
								sprintf(str, "%d", cpt);
								cairo_show_text (cr, str);
							}
						}
						cairo_destroy(cr);
						XNextEvent(dpy, &e);
						break;
					}
				}
				break;
			}
		}
	}
	cairo_surface_destroy(cs);
	XCloseDisplay(dpy);
}
