#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "serpent.h"


/*creer la tete du serpent et la positionner dans la grille */
struct tete_serpent *cree_serpent(int ligne_grille, int col_grille){
	struct tete_serpent *tete= malloc(sizeof(tete));
	if(tete==NULL){
		perror("erreur");
	}else{
		tete -> position_x = rand() % ( ligne_grille -2)+1 ;
		tete -> position_y = rand() % ( col_grille -2)+1 ;
		tete -> direction= rand() % 4  ;
		tete -> queue = NULL;

	}

	return tete;
}


void ajouter_element_serpent(struct tete_serpent *serpent){
	struct element_serpent *element_ptr= serpent -> queue;
	if(element_ptr){ /*si NULL alors il n'y a que la tete*/
		while(element_ptr -> queue){ /*chercher le dernier element*/
			element_ptr = element_ptr -> queue;
		}
		element_ptr -> queue =(struct element_serpent *) malloc(sizeof(element_ptr));
		element_ptr -> queue -> queue = NULL;
	}else{
	serpent -> queue =(struct element_serpent *) malloc(sizeof(element_ptr));
	serpent -> queue -> queue = NULL;
	}
}

int detection_echec(struct tete_serpent *serpent, int grille_x, int grille_y){
	int echec = 0;
	int tete_position_x = serpent -> position_x;
	int tete_position_y = serpent -> position_y;
	
	if(tete_position_x== 0 || tete_position_x >= grille_x -1|| tete_position_y == 0 || tete_position_y >= grille_y -1){
		echec =1;
	}else {
		struct element_serpent *element_ptr= serpent -> queue;
		while(element_ptr){
			if(tete_position_x == element_ptr -> position_x && tete_position_y == element_ptr -> position_y ){
			echec=1;
			break;
			}else{
			element_ptr = element_ptr -> queue;
			}
		}
	}
	
	return echec;
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

int deplacer_serpent(struct tete_serpent *serpent,int grille_x,int grille_y,int direction){
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
	
	/*deplacer le reste du serpent si il ya un reste */
	struct element_serpent *element_ptr= serpent -> queue;
	/*chaque element  prend la position de l'element qui le devance*/
	if(element_ptr){/*is NULL alors il ya que la tete du serpent */
		while(element_ptr -> queue){ /*sinon on fait deplacer la queue*/
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
	return detection_echec(serpent,grille_x,grille_y);
}

void desallouer_serpent(struct tete_serpent *serpent){
	struct element_serpent *element_ptr= serpent -> queue;
	free(serpent);
	while(element_ptr){
		struct element_serpent *element_ptr_tmp = element_ptr -> queue;
		free(element_ptr);
		element_ptr = element_ptr_tmp;
	}
}







