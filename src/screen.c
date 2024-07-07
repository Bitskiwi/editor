// INCLUDES

#include "screen.h"
#include <stdio.h>
#include <string.h>

// SCREEN CONSTRUCTOR

screen init_screen(){
	screen inst;
	return inst;
}

// SCREEN RESIZE

screen resize_screen(screen surf, int w, int h){
	surf.w = w;
	surf.h = h;
	return surf;
}

// SCREEN DRAW

screen draw_screen(screen surf, int x, int y, char letter[6], char fg[8], char bg[8]){
	strcpy(surf.letters[y][x], letter);
	strcpy(surf.fg[y][x], fg);
	strcpy(surf.bg[y][x], bg);
	return surf;
}

// SCREEN FILL

screen fill_screen(screen surf, char letter[6], char fg[8], char bg[8]){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			surf = draw_screen(surf, x, y, letter, fg, bg);
		}
	}
	return surf;
}

// SCREEN RENDER

void render_screen(screen surf){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			printf("%s",surf.letters[y][x]);
			printf("%s",surf.fg[y][x]);
			printf("%s",surf.bg[y][x]);
		}
		printf("\n");
	}
}
