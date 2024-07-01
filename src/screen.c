// INCLUDES

#include "screen.h"
#include <stdio.h>

// SCREEN CONSTRUCTOR

screen init_screen(){
	screen inst;
	return inst;
}

// SCREEN UPDATE

screen resize_screen(screen surf, int w, int h){
	surf.w = w;
	surf.h = h;
	return surf;
}

// SCREEN RENDER

void render_screen(screen surf){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			printf(surf.chars[y][x]);
		}
		printf("\n");
	}
}
