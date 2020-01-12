CC = gcc
CFLAGS1 = -g -Wall
CFLAGS2 = -Iinclude -I/usr/include/cairo
LDFLAGS = -lcairo -lm -lX11
vpath %.h include
vpath %.c src
vpath %.o obj
INC = include/
SRC = src/
OBJ = obj/
GR = grilles/

ifeq ($(MODE),TEXT)
	FILE = io
	FILEH = $(INC)io.h
	FILEC = $(SRC)io.c
	MAIN = main
	MAINC = $(SRC)main.c
else
	FILE = io_cairo
	FILEH = $(INC)io_cairo.h
	FILEC = $(SRC)io_cairo.c
	MAIN = main_cairo
	MAINC = $(SRC)main_cairo.c
endif

main: $(OBJ)$(MAIN).o $(OBJ)grille.o $(OBJ)$(FILE).o $(OBJ)jeu.o
	$(CC) $(CFLAGS1) -o $@ $? $(CFLAGS2) $(LDFLAGS)
	mkdir -p bin
	mv -f main ./bin/

$(OBJ)$(MAIN).o: $(MAINC) $(INC)jeu.h $(FILEH) $(INC)grille.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p $(OBJ)
	mv $(MAIN).o ./$(OBJ)

$(OBJ)grille.o : $(SRC)grille.c $(INC)grille.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p $(OBJ)
	mv grille.o ./$(OBJ)

$(OBJ)$(FILE).o : $(FILEC) $(FILEH)
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p $(OBJ)
	mv $(FILE).o ./$(OBJ)

$(OBJ)jeu.o : $(SRC)jeu.c $(INC)jeu.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p $(OBJ)
	mv jeu.o ./$(OBJ)

lib: $(OBJ)grille.o $(OBJ)$(FILE).o $(OBJ)jeu.o
	ar -crv libjeu.a $^
	ranlib libjeu.a
	mkdir -p lib
	mv libjeu.a ./lib/

dist : Makefile Doxyfile $(SRC) $(INC) $(GR) logo.png README.md
	tar -cvz $^ -f StavridisAdonis-GoL-V5.tar.xz

clean :
	rm -r bin $(OBJ) doc *.tar.xz
