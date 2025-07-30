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

// Glyph represents a drawable character with color
typedef struct {
	char symbol;
	int foregroundColor;
	int backgroundColor;
} Glyph;

// Screen represents a screen buffer
// Fields with a leading underscore are private and should not be modified directly.
typedef struct {
	Vector2 _size; // cannot be modified after init
	CHAR_INFO* _buffer; // 1D buffer for console data - x by y dynamically sized
	HANDLE* _output; // handle to the console output
} Screen;

// Initializes a new screen with the specified size and returns a dynamic reference.
Screen* screen_init(Vector2 size);

// Puts a glyph at the specified position on the screen.
// Returns 1 on success, 0 on failure/out of bounds.
int screen_putGlyph(Screen* screen, Glyph glyph, Vector2 pos);

// Clears terminal output.
void screen_clear(Screen* screen);

// Clears the screen buffer by filling it with null characters.
void screen_empty(Screen* screen);

// Fills the entire screen with the specified glyph.
void screen_fill(Screen* screen, Glyph glyph);

// Fills a rectangle on the screen with the specified glyph.
// Returns 1 on success, 0 on failure/out of bounds.
int screen_fillRect(Screen* screen, Transform t, Glyph glyph);

// Draws the current screen buffer to the console output.
void screen_draw(Screen* screen);

#endif // DRAW_H
