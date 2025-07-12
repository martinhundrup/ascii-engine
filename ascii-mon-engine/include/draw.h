/*
*	copyright martin hundrup
*/

/*
*	draw.h contains basic functionality for interacting
*	with the terminal window, including drawing, erasing,
*	color, etc.
*/

#ifndef DRAW_H
#define DRAW_H

#include "ascii-engine.h"

// Constants for common console colors
#define COLOR_BLACK         0
#define COLOR_BLUE          1
#define COLOR_GREEN         2
#define COLOR_CYAN          3
#define COLOR_RED           4
#define COLOR_MAGENTA       5
#define COLOR_YELLOW        6
#define COLOR_WHITE         7
#define COLOR_GRAY          8
#define COLOR_BRIGHT_BLUE   9
#define COLOR_BRIGHT_GREEN 10
#define COLOR_BRIGHT_CYAN  11
#define COLOR_BRIGHT_RED   12
#define COLOR_BRIGHT_MAGENTA 13
#define COLOR_BRIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

// Struct representing a drawable character with color
typedef struct {
	char symbol;
	int foregroundColor;
	int backgroundColor;
} Glyph;

HANDLE* configureDrawSystem();

int drawGlyph(HANDLE* handle, Vector2_Int* vect, Glyph* glyph);
int drawChar(HANDLE* handle, Vector2_Int* vect, char ch, int fgColor, int bgColor);
int clearScreen(HANDLE* handle);
int fillRect(HANDLE* handle, Vector2_Int* vect, int width, int height, Glyph* glyph);

int setCursorVisible(HANDLE* handle, int visible);
int moveCursor(HANDLE* handle, Vector2_Int* vect);

int eraseAtPosition(HANDLE* handle, Vector2_Int* vect);

#endif // DRAW_H
