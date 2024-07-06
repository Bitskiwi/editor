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

screen draw_screen(screen surf,)

// SCREEN FILL

screen fill_screen(screen surf, char letter[10], char fg[10], char bg[10]){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			surf = draw_screen(surf.map[y][x], fill_char, fg, bg);
		}
	}
	return surf;
}

// SCREEN RENDER

void render_screen(screen surf){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			printf(surf.map[y][x]);
		}
		printf("\n");
	}
}
