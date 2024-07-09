// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "screen.h"

// SET TERMINAL

void set_term(int i){
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	if(i == 1){
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
	*w = term.ws_col - 1;
	*h = term.ws_row - 1;
}

// MAIN

int main(){
	system("clear");
	set_term(1);
	int w, h;
	screen surf = init_screen();
	char key;
	get_term_size(&w, &h);
	surf = resize_screen(surf, w, h);
	surf = fill_screen(surf, " ", "", "");
	while(1){
		printf("\033[H");
		render_screen(surf);
		char key = getchar();
		if(key == 'q'){
			break;
		} else if (key >= 65 && key <= 90){
			surf = draw_screen(surf, 1, 1, "A", "\033[34m", "");
		}
	}
	set_term(0);
	system("clear");
}
