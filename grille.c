#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "grille.h"


struct grille * allouer_grille(int n , int m){
	struct grille * jeu_grille;
	int i,j;
	jeu_grille = malloc(sizeof(jeu_grille));
	/*creer tableau de pointeur qui pinte a son tour sur un autre tableau de pointeurs*/
	jeu_grille->tab =(char ***)malloc(sizeof(char **)*n);
	for (i=0;i<n ; i++){
	/*creer un tableau de m colonnes qui pointe vers un autre pointeur de chaine de caracteres*/
		jeu_grille->tab[i] =(char **)malloc(sizeof(char *)*m);
		for (j=0 ; j<m ; j++){
		/*creer un tableau de 8 caracteres (du code ansi)*/
			jeu_grille->tab[i][j] =(char *)malloc(sizeof(char)*8);
		}
	}
	jeu_grille->n = n;
	jeu_grille->m = m;
	
	jeu_grille->fruitX = 1;
	jeu_grille->fruitY = 1;
	return jeu_grille;
}
	
	
void grille_vider( struct grille *g){
int i,j;
	
	for(i=0 ; i< g -> n ; i++){
	   for(j=0 ; j< g -> m ; j++){
	   /*faire apparaitre les bordures en vert*/
	   	if(i==0 || j==0 || i== g -> n-1 || j== g -> m-1){
	   		strcpy(g -> tab[i][j],"\033[42m");
	   		/*printf("debug %s",g -> tab[i][j]);*/
	 	   	}else{
	 	   	/*faire apparaitre le fond en noir*/
			strcpy(g -> tab[i][j],"\x1b[40m");
			/*printf("debug %s",g -> tab[i][j]);*/
		}
	  }
	} 
}
void grille_redessiner(struct grille *g){

	int i,j;
	printf("n=%d :\n", g -> n);
	printf("m=%d :\n", g -> m);
	for(i=0 ; i< g -> n ; i++){
	   for(j=0 ; j< g -> m ; j++){
	   /*revenir a la couleur de texte normal sur fond noir*/
	   	printf("%s%s%s", g -> tab[i][j],"  ", "\033[0m" );
	  }
	  printf("\n");
	}

}
void grille_tirage_fruit( struct grille *g){
	srand(time(NULL));
	g->fruitX = rand() %( g -> n-2)+1 ;
	g->fruitY = rand() % (g -> m-2)+1 ;
}
void grille_remplir( struct grille *g, struct tete_serpent *tete){

	/*faire apparaitre le fruit en rouge aleatoirement*/
	strcpy(g -> tab[g -> fruitX][ g -> fruitY],"\033[41m");
	/*faire apparaitre la tete du serpent*/
	strcpy(g -> tab[tete-> position_x][tete -> position_y],"\033[43m");
	/*faire apparaitre le reste du serpent*/
	struct element_serpent *element_ptr=tete -> queue;
	while(element_ptr){
		strcpy(g -> tab[element_ptr-> position_x][element_ptr -> position_y],"\033[41m");
		element_ptr = element_ptr -> queue;
	}
}

void desallouer_grille(struct grille *g){
	int i,j;
	for(i=0; i< g -> n ; i++){
		for(j=0; j< g -> m ; j++){
			free(g -> tab[i][j]);
		}
			free(g -> tab[i]);
	}
			free(g -> tab);

}

