all: grille.o  serpent.o main.o
	gcc grille.o serpent.o main.o -o programme
grille.o: grille.c grille.h
	gcc -c -Wall -Wfatal-errors -ansi grille.c
serpent.o: serpent.c serpent.h
	gcc -c -Wall -Wfatal-errors -ansi serpent.c

main.o : main.c
	 gcc -c -Wall -Wfatal-errors -ansi main.c
clean: 
	rm *.o programme
