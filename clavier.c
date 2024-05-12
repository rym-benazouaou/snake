/*cette partie du code je l'ai genere via chatgpt*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include "clavier.h"

int get_direction() {
    struct termios org_opts, new_opts;
    char c;
    int direction = -1;

    /*Get current terminal settings*/
    if (tcgetattr(STDIN_FILENO, &org_opts) != 0) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    /* Copy current settings to new settings*/
    new_opts = org_opts;

    /* Disable canonical mode and echoing*/
    new_opts.c_lflag &= ~(ICANON | ECHO);

    /* Set a timeout for non-blocking read*/
    new_opts.c_cc[VMIN] = 0;
    new_opts.c_cc[VTIME] = 20; /* Timeout in tenths of a second (2 seconds)*/

    /*Apply new settings*/
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_opts) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    /* Read one character*/
    ssize_t nread = read(STDIN_FILENO, &c, 1);

    /*Restore original terminal settings*/
    if (tcsetattr(STDIN_FILENO, TCSANOW, &org_opts) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    /* Check if a character is read*/
    if (nread == 1) {
        switch (c) {
            case 'w':
            case 'W':
                direction = 0; /* UP*/
                break;
            case 'a':
            case 'A':
                direction = 1; /* LEFT*/
                break;
            case 'd':
            case 'D':
                direction = 2; /*RIGHT*/
                break;
            case 's':
            case 'S':
                direction = 3; /*DOWN*/
                break;
            default:
                direction = -1; /* Other keys*/
                break;
        }
    }

    return direction;
}




	

