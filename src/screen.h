// HEADER GUARD

#ifndef SCREEN_H
#define SCREEN_H

// SCREEN STRUCTURE

typedef struct screen {
	int w;
	int h;
	char map[300][300][10];
} screen;

// SCREEN CONSTRUCTOR

screen new_screen();

#endif
