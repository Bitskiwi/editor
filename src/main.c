// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "screen.h"

// SET TERMINAL

void set_term(int x){
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	if(x == 1){
		term.c_lflag &= ~(ICANON | ECHO);
	} else {
		term.c_lflag |= (ICANON | ECHO);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// GET TERMINAL SIZE

void get_term_size(int *w, int *h){
	struct winsize term;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &term);
	*w = term.ws_col;
	*h = term.ws_row;
}

// MAIN

int main(){
	system("clear");
	set_term(1);
	int w, h;
	screen surf = init_screen();
	char key;
	while(1){
		printf("\033[H");
		get_term_size(&w, &h);
		surf = resize_screen(surf, w, h);
		render_screen(surf);
		char key = getchar();
		if(key == 'q'){
			break;
		}
	}
	set_term(0);
	system("clear");
}
