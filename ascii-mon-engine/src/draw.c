/*
*	copyright martin hundrup
*/

/*
*	draw.c contains the function impelementations for drawing.
*/

#include "../include/draw.h"

Screen* screen_init(Vector2_Int size){
	Screen* screen = (Screen*)malloc(sizeof(Screen));
	screen->_size = size;
	screen->_buffer = (CHAR_INFO*)malloc(size.x * size.y * sizeof(CHAR_INFO));
	screen->_output = (HANDLE*)malloc(sizeof(HANDLE));
	*screen->_output = GetStdHandle(STD_OUTPUT_HANDLE);
	return screen;
}

int screen_putGlyph(Screen* screen, Glyph glyph, Vector2_Int pos){
	if (!checkBounds(screen->_size, pos)) return 0;
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

int screen_fillRect(Screen* screen, Vector2_Int origin, Vector2_Int size, Glyph glyph){
	if (!screen || !screen->_buffer) return 0;
	if (!checkBounds(screen->_size, origin) || !checkBounds(screen->_size, 
		(Vector2_Int){origin.x + size.x - 1, origin.y + size.y - 1})) return 0;

	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			Vector2_Int pos = {origin.x + x, origin.y + y};
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

int checkBounds(Vector2_Int size, Vector2_Int pos){
	return (pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y);
}

// HANDLE* configureDrawSystem() {
//   HANDLE* output = (HANDLE*)malloc(sizeof(HANDLE));
// 	*output = GetStdHandle(STD_OUTPUT_HANDLE);
//   return output;
// }

// int drawGlyph(HANDLE* handle, Vector2_Int* vect, Glyph* glyph) {
// 	if (!handle || !vect || !glyph) return -1;
// 	if (vect->x < 0 || vect->y < 0) return -2;
// 	CONSOLE_SCREEN_BUFFER_INFO csbi;
// 	if (!GetConsoleScreenBufferInfo(*handle, &csbi)) {
// 		return -3; // Failsafe: can't get original attributes
// 	}
// 	COORD pos = { (SHORT)vect->x, (SHORT)vect->y };
// 	if (!SetConsoleCursorPosition(*handle, pos)) return -4;
// 	if (!SetConsoleTextAttribute(*handle, (WORD)((glyph->backgroundColor << 4) | glyph->foregroundColor))) return -5;
// 	putchar(glyph->symbol);
// 	// Restore original attributes
// 	if (!SetConsoleTextAttribute(*handle, csbi.wAttributes)) return -6;
// 	return 0;
// }

// int drawChar(HANDLE* handle, Vector2_Int* vect, char ch, int fgColor, int bgColor) {
// 	Glyph glyph = { ch, fgColor, bgColor };
// 	return drawGlyph(handle, vect, &glyph);
// }

// int clearScreen(HANDLE* handle) {
// 	if (!handle) return -1;
// 	CONSOLE_SCREEN_BUFFER_INFO csbi;
// 	if (!GetConsoleScreenBufferInfo(*handle, &csbi)) return -2;
// 	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
// 	COORD topLeft = { 0, 0 };
// 	DWORD written;
// 	if (!FillConsoleOutputCharacter(*handle, ' ', consoleSize, topLeft, &written)) return -3;
// 	if (!FillConsoleOutputAttribute(*handle, csbi.wAttributes, consoleSize, topLeft, &written)) return -4;
// 	if (!SetConsoleCursorPosition(*handle, topLeft)) return -5;
// 	return 0;
// }

// int fillRect(HANDLE* handle, Vector2_Int* origin, Vector2_Int* size, Glyph* glyph) {
// 	if (!handle || !origin || !size || !glyph) return -1;
// 	if (origin->x < 0 || origin->y < 0 || size->x < 0 || size->y < 0) return -2;
// 	int err = 0;
// 	for (int row = 0; row < size->y; row++) {
// 		for (int col = 0; col < size->x; col++) {
// 			Vector2_Int v = {origin->x + col, origin->y + row};
// 			int res = drawGlyph(handle, &v, glyph);
// 			if (res != 0) err = res;
// 		}
// 	}
// 	return err;
// }

// int setCursorVisible(HANDLE* handle, int visible) {
// 	if (!handle) return -1;
// 	CONSOLE_CURSOR_INFO cursorInfo;
// 	if (!GetConsoleCursorInfo(*handle, &cursorInfo)) return -2;
// 	cursorInfo.bVisible = visible ? TRUE : FALSE;
// 	if (!SetConsoleCursorInfo(*handle, &cursorInfo)) return -3;
// 	return 0;
// }

// int moveCursor(HANDLE* handle, Vector2_Int* vect) {
// 	if (!handle || !vect) return -1;
// 	if (vect->x < 0 || vect->y < 0) return -2;
// 	COORD pos = { (SHORT)vect->x, (SHORT)vect->y };
// 	if (!SetConsoleCursorPosition(*handle, pos)) return -3;
// 	return 0;
// }

// int eraseAtPosition(HANDLE* handle, Vector2_Int* vect) {
// 	if (!handle || !vect) return -1;
// 	if (vect->x < 0 || vect->y < 0) return -2;
// 	CONSOLE_SCREEN_BUFFER_INFO csbi;
// 	if (!GetConsoleScreenBufferInfo(*handle, &csbi)) {
// 		return -3;
// 	}
// 	COORD pos = { (SHORT)vect->x, (SHORT)vect->y };
// 	DWORD written;
// 	if (!FillConsoleOutputCharacter(*handle, ' ', 1, pos, &written)) return -4;
// 	if (!FillConsoleOutputAttribute(*handle, csbi.wAttributes, 1, pos, &written)) return -5;
// 	return 0;
// }