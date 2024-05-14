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
	int nouvelle_direction;
	int tirage_necessaire=0;
	int echec=0;
	printf("le grille fait %d lignes et %d colonnes\n", n,m);
	srand(time(NULL));
	struct grille * jeu_grille = allouer_grille( n , m);
	grille_tirage_fruit (jeu_grille);
	struct tete_serpent *serpent = cree_serpent(n,m);
	ajouter_element_serpent(serpent);
	
	while(1){
		printf("\33[2J");
		printf("\33[H");
		grille_vider (jeu_grille);
		grille_remplir(jeu_grille,serpent);
		grille_redessiner(jeu_grille);
		if((serpent ->position_x == jeu_grille -> fruitX) && (serpent ->position_y == jeu_grille -> fruitY)){
			ajouter_element_serpent(serpent);
			tirage_necessaire=1;
		}
		nouvelle_direction = touche_clavier() ;
		echec = deplacer_serpent(serpent,jeu_grille -> n, jeu_grille ->m,nouvelle_direction);
		if(echec){
			printf("\33[2J");
			printf("\33[H");
			printf("Game Over !!!\n");
			grille_desallouer(jeu_grille);
			desallouer_serpent(serpent);
			return 0;
		}
		
		if(tirage_necessaire){
			grille_tirage_fruit (jeu_grille);
			tirage_necessaire =0;
		}
			
		
	}
	
return 0;
}
