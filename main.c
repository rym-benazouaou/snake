#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include "grille.h"
#include "serpent.h"
#include "clavier.h"


int main(int argc, char *argv[]){
	if(argc != 3){
		printf("erreur, usage : %s <nombre_de_ligne> <nombre_de_colonne>\n", argv[0]);
	return 1;
	}
int n = atoi(argv[1]);
int m = atoi(argv[2]);
	printf("le grille fait %d lignes et %d colonnes\n", n,m);
	/*struct couleur couleur;*/
	struct grille * jeu_grille = allouer_grille( n , m);
	struct tete_serpent *serpent = cree_serpent(n,m);
	int nouvelle_direction;
	int tirage_necessaire=0;
	
	grille_tirage_fruit (jeu_grille);
	while(1){
		printf("\33[2J");
		grille_vider (jeu_grille);
		grille_remplir(jeu_grille,serpent);
		grille_redessiner(jeu_grille);
		if((serpent ->position_x == jeu_grille -> fruitX) && (serpent ->position_y == jeu_grille -> fruitY)){
			ajouter_element_serpent(serpent);
			tirage_necessaire=1;
		}
		srand(time(NULL));
			nouvelle_direction = get_direction() ;
			/*ignorer les demi tour */
			switch(nouvelle_direction){
				case 0:
					if(serpent -> direction ==3) nouvelle_direction =3;
					break;
				case 1:
					if(serpent -> direction ==2) nouvelle_direction =2;
					break;
				case 2:
					if(serpent -> direction ==1) nouvelle_direction =1;
					break;
				case 3:
					if(serpent -> direction ==0) nouvelle_direction =0;
					break;
				default : 
					nouvelle_direction= serpent ->direction;
			}
			deplacer_serpent(serpent, nouvelle_direction);
			if(tirage_necessaire){
				grille_tirage_fruit (jeu_grille);
				tirage_necessaire =0;
			}
		
	}
	
return EXIT_SUCCESS;
}
