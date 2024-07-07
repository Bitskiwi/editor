// INCLUDES

#include "glyph.h"
#include <stdio.h>
#include <string.h>

// GLYPH CONSTRUCTOR

glyph init_glyph(char letter[10], char fg[10], char bg[10]){
	glyph inst;
	strcpy(inst.letter, letter);
	strcpy(inst.fg, fg);
	strcpy(inst.bg, bg);
	return inst;
}

// GLYPH RENDER

void render_glyph(glyph gly){
	printf("%s", gly.fg);
	printf("%s", gly.bg);
	printf("%s", gly.letter);
}
