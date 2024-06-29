// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "canvas.h"

// MAIN

int main(){
	system("clear");
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	char key;
	while(1){
		printf("\033[H");
		canvas surf = new_canvas();
		char key = getchar();
		if(key == 'q'){
			break;
		}
	}
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	system("clear");
}
