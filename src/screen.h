// HEADER GUARD

#ifndef SCREEN_H
#define SCREEN_H

// SCREEN STRUCTURE

typedef struct screen {
	int w;
	int h;
	char chars[200][200][10];
} screen;

// SCREEN CONSTRUCTOR

screen init_screen();

// SCREEN UPDATE

screen resize_screen(screen surf, int w, int h);

// SCREEN RENDER

void render_screen();

#endif
