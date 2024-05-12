#ifndef GRILLE_H
#define GRILLE_H
#include "serpent.h"
struct grille{
	int m;
	int n; 
	char *** tab;
	int fruitX;
	int fruitY;
};

struct grille * allouer_grille(int m, int n);

void grille_vider( struct grille *g);
void grille_afficher(struct grille *g);
void grille_tirage_fruit(struct grille *g);
void grille_remplir(struct grille *g, struct tete_serpent *tete);
void grille_desallouer(struct grille *g);
void grille_redessiner(struct grille *g);

#endif
