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
	
	
	while(1){
		/*system("clear");*/
		printf("\33[2J");
		grille_vider (jeu_grille);
		grille_tirage_fruit (jeu_grille);
		grille_remplir(jeu_grille,serpent);
		grille_afficher(jeu_grille);
		ajouter_element_serpent(serpent);
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
	}
	
return EXIT_SUCCESS;
}
