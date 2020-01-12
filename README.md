# Game of Life

----

This is a Game of Life built in C and using Cairo.

----

### Overview

This program can be run in two different configurations: one with a graphical interface and a second with a terminal interface.

If you have chosen the graphical interface, then a grid will appear with the following information:
- **Evolution** indicates the generation number of the current grid
- **Cyclic** indicates if neighbors are calculated cyclically or not
- **Aging** indicates whether aging is activated or not

In the grid:
- empty cells and dead cells
- cells in dark gray color are living cells
- cells in black color are non-viable cells

The application awaits for input. The possible commands are the following:
- **Left Mouse Click** advances to next generation
- **N** change the grid, you then have to choose a grid name in the terminal in the format ./grilles/<grille_number.txt>
- **C** activates or deactivates cyclic neighbor calculation
- **V** activates or deactivates aging of the cells
- **O** test if a colony is oscillating
- **Right Mouse Click** closes the application

Le programme attend maintenant une instruction de la part de l'utilisateur. Vous pouvez taper les touches suivantes:
+ <clique de souris gauche\>: pour passer à l'évolution suivante
+ 'n': pour changer de grille -> il faut alors choisir une autre grille en écrivant ./grilles/<nom_fichier_grille> dans le terminal
+ 'c': pour changer de méthode de calcul du voisinage des cellules (passer du calcul cyclique à non-cyclique et inversement)
+ 'v': pour activer ou désactiver le vieillissement des cellules
+ 'o': pour tester si une colonie est oscillante
+ <clique de souris droit>: pour quitter le programme

If you have chosen the terminal interface there are a few changes.

The grid is represented like this:

    |---|---|---|---|---|
    |   |   |   |   |   |
    |---|---|---|---|---|
    |   |   |   |   |   |
    |---|---|---|---|---|
    |   |   |   |   |   |
    |---|---|---|---|---|

Empty cells are dead cells, those represented by **O** are living cells, by **X** are non-viable cells.

The input differences are the following:
- **Enter** instead of **Left Mouse Click**
- **q Enter** instead of **Right Mouse Click**

For more information concerning the application, you can also look up the Doxygen documentation.

### Compile and Run

In order to compile this application, you need to run the first command for a graphical interface and the second for a terminal interface.

    make
    make MODE=TEXT

You can then run the application from the same directory with the following command:

    ./bin/main ./grilles/<grille_number.txt>

If you have compiled the program with `MODE=TEXT` it is recommended to set the terminal to full screen.
