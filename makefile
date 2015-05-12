main: grille.o main.o personnage.o affichage.o argv.o chemin.o
main: grille.o main.o personnage.o affichage.o argv.o chemin.o
main: grille.o main.o personnage.o affichage.o argv.o chemin.o
main: grille.o main.o personnage.o affichage.o argv.o chemin.o
main: grille.o main.o personnage.o affichage.o argv.o chemin.o
	gcc -o bin/app compile/grille.o compile/personnage.o compile/main.o compile/argv.o compile/affichage.o compile/chemin.o -lncurses

grille.o: src/grille.c include/grille.h
	gcc -o compile/grille.o -c src/grille.c -I include/

personnage.o: src/personnage.c include/personnage.h
	gcc -o compile/personnage.o -c src/personnage.c -I include/

argv.o: src/argv.c
	gcc -o compile/argv.o -c src/argv.c

affichage.o: src/affichage.c include/affichage.h
	gcc -o compile/affichage.o -c src/affichage.c -I include/ -lncurses

chemin.o: src/chemin.c
	gcc -o compile/chemin.o -c src/chemin.c -I include/ -lncurses

main.o: src/main.c include/grille.h
	gcc -o compile/main.o -c src/main.c -I include/ -lncurses

gestion.o: src/gestion.c include/gestion.h
	gcc -o compile/gestion.o -c src/gestion.c -I include/

objet.o: src/objet.c include/objet.h
	gcc -o compile/objet.o -c src/objet.c -I include/

deplacement.o: src/deplacement.c include/deplacement.h
	gcc -o compile/deplacement.o -c src/deplacement.c -I include/

jeu.o: src/jeu.c include/jeu.h
	gcc -o compile/jeu.o -c src/jeu.c -I include/





#============================================
SDL: SDL_affichage.o grille.o personnage.o main.o controle.o gestion.o deplacement.o objet.o jeu.o
	gcc -o bin/SDL_app compile/SDL_affichage.o compile/grille.o compile/controle.o compile/deplacement.o compile/main.o compile/personnage.o compile/gestion.o compile/objet.o compile/jeu.o -lSDL -Wall

SDL_affichage.o: src/SDL_affichage.c
	gcc -o compile/SDL_affichage.o -c src/SDL_affichage.c -I include/
controle.o: src/controle.c
	gcc -o compile/controle.o -c src/controle.c -I include/

clean_objet:
	rm -rf compile/*
clean_bin:
	rm -rf bin/*
clean_dhydrogen:
	rm -rf html/*
	rm Doxyfile

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

run: bin/SDL_app
	./bin/SDL_app ressources/001.map
valgrind: bin/SDL_app
	valgrind ./bin/SDL_app ressources/001.map
valgrind-leak: bin/SDL_app
	valgrind --leak-check=full ./bin/SDL_app ressources/001.map
