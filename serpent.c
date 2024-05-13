#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "serpent.h"
#include "grille.h"

/*creer la tete du serpent et la positionner dans la grille */
struct tete_serpent *cree_serpent(int ligne_grille, int col_grille){
	struct tete_serpent *tete= malloc(sizeof(tete));
	if(tete==NULL){
		perror("erreur");
	}else{
		srand(time(NULL));
		tete -> position_x = rand() % ( ligne_grille -2)+1  ;
		tete -> position_y = rand() % ( col_grille -2)+1  ;
		tete -> direction= rand() % 4  ;
		tete -> position_dans_la_chaine= 1  ;
		tete -> queue = NULL;

	}

	return tete;
}


void ajouter_element_serpent(struct tete_serpent *serpent){
	struct element_serpent *element_ptr= serpent -> queue;
	/*chercher le dernier element*/
	if(element_ptr){
		while(element_ptr -> queue){
			element_ptr = element_ptr -> queue;
		}
		element_ptr -> queue =(struct element_serpent *) malloc(sizeof(element_ptr));
		element_ptr -> queue -> position_dans_la_chaine =element_ptr -> position_dans_la_chaine ++;
		element_ptr -> queue -> queue = NULL;
	}else{
	serpent -> queue =(struct element_serpent *) malloc(sizeof(element_ptr));
	serpent -> queue -> position_dans_la_chaine =serpent -> position_dans_la_chaine ++;
	serpent -> queue -> queue = NULL;
	}
}
void haut(struct tete_serpent *serpent){
	serpent -> position_x --;
}

void bas(struct tete_serpent *serpent){
	serpent -> position_x ++;
}

void gauche(struct tete_serpent *serpent){
	serpent -> position_y --;
}

void droite(struct tete_serpent *serpent){
	serpent -> position_y ++;
}

void deplacer_serpent(struct tete_serpent *serpent,int direction){
	int position_x = serpent -> position_x;
	int position_y = serpent -> position_y;
	if (direction == -1 ){
		direction = serpent -> direction;
	}
	int direction_courante = serpent -> direction;
	/*deplacer la tete du serpent*/
	switch(direction){
		case 0:/*haut*/
			if(direction_courante == 3){ /*bas: eviter les demi tour ,on continue vers lebas*/
				bas(serpent);
			}else{
				haut(serpent);
				serpent -> direction = direction;
			}
			break;
		case 1:/*gauche*/
			if(direction_courante == 2){ /*droite: eviter les demi tour ,on continue vers la droite*/
				droite(serpent);
			}else{
				gauche(serpent);
				serpent -> direction = direction;
			}
			break;
		case 2:/*droite*/
			if(direction_courante == 1){ /*gauche: eviter les demi tour ,on continue vers la gauche*/
				gauche(serpent);
			}else{
				droite(serpent);
				serpent -> direction = direction;
			}
			break;
		case 3:/*bas*/
			if(direction_courante == 0){ /*haut: eviter les demi tour ,on continue vers le haut*/
				haut(serpent);
			}else{
				bas(serpent);
				serpent -> direction = direction;
			}
			break;
		default:
			printf("erreur");
	}
	
	/*deplacer le reste du serpent*/
	struct element_serpent *element_ptr= serpent -> queue;
	/*chaque element  prend la position de l'element qui le devance*/
	while(element_ptr -> queue){
		int x,y;
		x = element_ptr -> position_x; 
		element_ptr -> position_x = position_x;
		position_x = x;
		y = element_ptr -> position_y; 
		element_ptr -> position_y = position_y;
		position_y = y;
		element_ptr = element_ptr -> queue;
	}
	/*deplacer le dernier element*/
	element_ptr -> position_x = position_x;
	element_ptr -> position_y = position_y;

}









