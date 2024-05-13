#include<ncurses.h>

int touche_clavier() {


  int ch, touche;


  /* Initialisation de ncurses et du clavier(4 lignes)*/
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();


  halfdelay(10);  /* Temps d'exécution max de getch à 1/10eme de seconde */
  ch = getch();



  switch(ch) {  
        case KEY_UP:  
           touche = 0;
           break;
        case KEY_DOWN: 
           touche = 3;
           break;
        case KEY_LEFT: 
           touche = 1;
           break; 
        case KEY_RIGHT: 
           touche = 2;
           break;
        default:
           touche = -1;
           break;
   }
      

   
   
  endwin(); /* Doit obligatoirement etre mis en fin de programme pour remettre le terminal en etat */
  



  return touche;


}




	

