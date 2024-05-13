all: grille.o  serpent.o clavier.o main.o
	gcc grille.o serpent.o clavier.o main.o -o programme -lncurses
grille.o: grille.c grille.h
	gcc -c -Wall -Wfatal-errors -ansi grille.c
serpent.o: serpent.c serpent.h
	gcc -c -Wall -Wfatal-errors -ansi serpent.c
clavier.o: clavier.c clavier.h
	gcc -c -Wall -Wfatal-errors -ansi clavier.c

main.o : main.c
	 gcc -c -Wall -Wfatal-errors -ansi main.c
clean: 
	rm *.o programme
