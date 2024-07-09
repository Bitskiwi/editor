// HEADER GUARD

#ifndef SCREEN_H
#define SCREEN_H

// DEV EXP

#define max 160

// SCREEN STRUCTURE

typedef struct screen {
	int w;
	int h;
	char letters[max][max][6];
	char fg[max][max][8];
	char bg[max][max][8];
} screen;

// SCREEN CONSTRUCTOR

screen init_screen();

// SCREEN UPDATE

screen resize_screen(screen surf, int w, int h);

// SCREEN DRAW

screen draw_screen(screen surf, int x, int y, char letter[6], char fg[8], char bg[8]);

// SCREEN FILL

screen fill_screen(screen surf, char letter[6], char fg[8], char bg[8]);

// SCREEN RENDER

void render_screen();

#endif
