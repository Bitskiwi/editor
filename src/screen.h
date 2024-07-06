// HEADER GUARD

#ifndef SCREEN_H
#define SCREEN_H

// INCLUDES

#include "glyph.h"

// SCREEN STRUCTURE

typedef struct screen {
	int w;
	int h;
	glyph map[200][200][30];
} screen;

// SCREEN CONSTRUCTOR

screen init_screen();

// SCREEN UPDATE

screen resize_screen(screen surf, int w, int h);

// SCREEN FILL

screen fill_screen(screen surf, char *fill);

// SCREEN RENDER

void render_screen();

#endif
