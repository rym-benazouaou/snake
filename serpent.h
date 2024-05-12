#ifndef SERPENT_H
#define SERPENT_H

struct element_serpent{
	int position_x;
	int position_y;
	int position_dans_la_chaine;
	struct element_serpent *queue;
};
struct tete_serpent{
	int position_x;
	int position_y;
	int position_dans_la_chaine;
	char direction;
	struct element_serpent *queue;
};

struct tete_serpent *cree_serpent(int position_x, int position_y);
void ajouter_element_serpent(struct tete_serpent *serpent);
void deplacer_serpent(struct tete_serpent *serpent,int direction);
/*struct serpent *cree_element(int position_x, int position_y);
void detruire_serpent(struct serpent *serpent);
void ajouter_section(struct serpent *serpent, struct couleur couleur);*/

#endif
