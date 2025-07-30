/*
*	copyright martin hundrup
*/

/*
*	draw.c contains the function impelementations for drawing.
*/

#include "../include/draw.h"

Screen* screen_init(Vector2 size){
	Screen* screen = (Screen*)malloc(sizeof(Screen));
	screen->_size = size;
	screen->_buffer = (CHAR_INFO*)malloc(size.x * size.y * sizeof(CHAR_INFO));
	screen->_output = (HANDLE*)malloc(sizeof(HANDLE));
	*screen->_output = GetStdHandle(STD_OUTPUT_HANDLE);
	return screen;
}

int screen_putGlyph(Screen* screen, Glyph glyph, Vector2 pos){
	if (!checkBounds((Transform){pos, {1, 1}}, (Transform){{0, 0}, screen->_size})) return 0;
	int index = pos.y * screen->_size.x + pos.x;
	screen->_buffer[index].Char.AsciiChar = glyph.symbol;
	screen->_buffer[index].Attributes = (WORD)((glyph.backgroundColor << 4) | glyph.foregroundColor);
	return 1;
}

void screen_empty(Screen* screen){
	if (!screen || !screen->_buffer) return;
	memset(screen->_buffer, 0, screen->_size.x * screen->_size.y * sizeof(CHAR_INFO));
}

void screen_clear(Screen* screen){
	if (!screen || !screen->_output) return;
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(*screen->_output, &csbi)) return;
	
	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD topLeft = { 0, 0 };
	DWORD written;
	
	// Clear all characters with spaces
	FillConsoleOutputCharacter(*screen->_output, ' ', consoleSize, topLeft, &written);
	// Reset all attributes to default
	FillConsoleOutputAttribute(*screen->_output, csbi.wAttributes, consoleSize, topLeft, &written);
	// Move cursor to top-left
	SetConsoleCursorPosition(*screen->_output, topLeft);
}

void screen_fill(Screen* screen, Glyph glyph){
	if (!screen || !screen->_buffer) return;
	CHAR_INFO charInfo;
	charInfo.Char.AsciiChar = glyph.symbol;
	charInfo.Attributes = (WORD)((glyph.backgroundColor << 4) | glyph.foregroundColor);
	
	for (int i = 0; i < screen->_size.x * screen->_size.y; i++) {
		screen->_buffer[i] = charInfo;
	}
}

int screen_fillRect(Screen* screen, Transform t, Glyph glyph){
	if (!screen || !screen->_buffer) return 0;
	if (t.size.x <= 0 || t.size.y <= 0) return 0;
	if (!checkBounds(t, (Transform){{0, 0}, screen->_size})) return 0;

	for (int y = 0; y < t.size.y; y++) {
		for (int x = 0; x < t.size.x; x++) {
			Vector2 pos = {t.position.x + x, t.position.y + y};
			screen_putGlyph(screen, glyph, pos);
		}
	}
	return 1;
}

void screen_draw(Screen* screen){
	if (!screen || !screen->_output || !screen->_buffer) return;
	
	// Write the buffer directly to console - no conversion needed!
	COORD bufferSize = {(SHORT)screen->_size.x, (SHORT)screen->_size.y};
	COORD bufferCoord = {0, 0};
	SMALL_RECT writeRegion = {0, 0, (SHORT)(screen->_size.x - 1), (SHORT)(screen->_size.y - 1)};
	
	WriteConsoleOutput(*screen->_output, screen->_buffer, bufferSize, bufferCoord, &writeRegion);
}
