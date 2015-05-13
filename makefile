#============================================
#         VARIABLE
#============================================

libs=-lSDL
warning=-Wall
opti=-O2
out=bin/SDL_app
map=ressources/001.map
INCLUDE=-I include

DEP=SDL_affichage.o grille.o controle.o deplacement.o main.o personnage.o gestion.o objet.o jeu.o monstre.o
OBJETS=compile/SDL_affichage.o compile/grille.o compile/controle.o compile/deplacement.o compile/main.o compile/personnage.o compile/gestion.o compile/objet.o compile/jeu.o compile/monstre.o

#============================================
#       MAIN
#============================================

main: $(DEP)
	gcc -o $(out) $(OBJETS) $(libs) $(warning) $(opti)

#============================================
#               OBJETS
#============================================

grille.o: src/grille.c include/grille.h
	gcc -o compile/grille.o -c src/grille.c $(INCLUDE)

personnage.o: src/personnage.c include/grille.h include/SDL_affichage.h include/controle.h include/objet.h include/personnage.h
	gcc -o compile/personnage.o -c src/personnage.c $(INCLUDE)

argv.o: src/argv.c
	gcc -o compile/argv.o -c src/argv.c

gestion.o: src/gestion.c include/grille.h include/objet.h include/personnage.h include/gestion.h include/SDL_affichage.h
	gcc -o compile/gestion.o -c src/gestion.c $(INCLUDE)

objet.o: src/objet.c include/SDL_affichage.h include/objet.h
	gcc -o compile/objet.o -c src/objet.c $(INCLUDE)

deplacement.o: src/deplacement.c include/deplacement.h include/personnage.h include/gestion.h include/grille.h
	gcc -o compile/deplacement.o -c src/deplacement.c $(INCLUDE)

jeu.o: src/jeu.c include/personnage.h include/grille.h include/controle.h include/objet.h include/SDL_affichage.h include/gestion.h include/deplacement.h
	gcc -o compile/jeu.o -c src/jeu.c $(INCLUDE)

monstre.o: src/monstre.c include/monstre.h include/personnage.h include/SDL_affichage.h
	gcc -o compile/monstre.o -c src/monstre.c $(INCLUDE)

SDL_affichage.o: src/SDL_affichage.c include/SDL_affichage.h include/grille.h include/objet.h include/personnage.h
	gcc -o compile/SDL_affichage.o -c src/SDL_affichage.c $(INCLUDE)

controle.o: src/controle.c include/controle.h include/grille.h
	gcc -o compile/controle.o -c src/controle.c $(INCLUDE)

main.o: src/main.c include/personnage.h include/grille.h include/controle.h include/objet.h include/SDL_affichage.h include/gestion.h include/deplacement.h
	gcc -o compile/main.o -c src/main.c $(INCLUDE) -lncurses

#============================================
#       CLEAN
#============================================
clean_objet:
	rm -rf compile/*.o
clean_bin:
	rm -rf bin/*
clean_dhydrogen:
	rm -rf html/*
	rm Doxyfile

#============================================
#        DOXYGEN
#============================================
dhydrogen: #blague
	doxygen -g
	sed -i 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/g' Doxyfile
	sed -i 's/INLINE_SOURCES         = NO/INLINE_SOURCES         = YES/g' Doxyfile
	sed -i 's/GENERATE_LATEX         = YES/GENERATE_LATEX         = NO/g' Doxyfile
	cp -r src/* ./
	cp -r include/* ./
	doxygen
	rm -rf *.c
	rm -rf *.h

#============================================	
#         EXECUTION
#============================================
run: bin/SDL_app
	./$(out) $(map)
valgrind: bin/SDL_app
	valgrind ./$(out) $(map)
valgrind-leak: bin/SDL_app
	valgrind --leak-check=full ./$(out) $(map)
