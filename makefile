bite::

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
