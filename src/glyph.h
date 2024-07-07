// HEADER GUARD

#ifndef GLYPH_H
#define GLYPH_H

// GLYPH STRUCTURE

typedef struct {
	char letter[10];
	char fg[10];
	char bg[10];
} glyph;

// GLYPH CONSTRUCTOR

glyph init_glyph(char letter[10], char fg[10], char bg[10]);

// GLYPH RENDER

void render_glyph(glyph gly);

#endif
