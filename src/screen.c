// INCLUDES

#include "screen.h"
#include <stdio.h>
#include <string.h>
#include "glyph.h"

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

screen draw_screen(screen surf, int x, int y, glyph gly){
	surf.map[y][x] = gly;
	return surf;
}

// SCREEN FILL

screen fill_screen(screen surf, glyph gly){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			surf = draw_screen(surf, x, y, gly);
		}
	}
	return surf;
}

// SCREEN RENDER

void render_screen(screen surf){
	for(int y = 0; y < surf.h; y++){
		for(int x = 0; x < surf.w; x++){
			render_glyph(surf.map[y][x]);
		}
		printf("\n");
	}
}
