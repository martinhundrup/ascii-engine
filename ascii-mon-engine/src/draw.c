/*
*	copyright martin hundrup
*/

/*
*	draw.c contains the function impelementations for drawing.
*/

#include "../include/draw.h"

// Initialization and teardown
HANDLE* configureDrawSystem() {
  HANDLE* output = (HANDLE*)malloc(sizeof(HANDLE));
	*output = GetStdHandle(STD_OUTPUT_HANDLE);
  return output;
}

// Drawing functions

int drawGlyph(HANDLE* handle, Vector2_Int* vect, Glyph* glyph) {
	if (!handle || !vect || !glyph) return -1;
	if (vect->x < 0 || vect->y < 0) return -2;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(*handle, &csbi)) {
		return -3; // Failsafe: can't get original attributes
	}
	COORD pos = { (SHORT)vect->x, (SHORT)vect->y };
	if (!SetConsoleCursorPosition(*handle, pos)) return -4;
	if (!SetConsoleTextAttribute(*handle, (WORD)((glyph->backgroundColor << 4) | glyph->foregroundColor))) return -5;
	putchar(glyph->symbol);
	// Restore original attributes
	if (!SetConsoleTextAttribute(*handle, csbi.wAttributes)) return -6;
	return 0;
}


int drawChar(HANDLE* handle, Vector2_Int* vect, char ch, int fgColor, int bgColor) {
	Glyph glyph = { ch, fgColor, bgColor };
	return drawGlyph(handle, vect, &glyph);
}


int clearScreen(HANDLE* handle) {
	if (!handle) return -1;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(*handle, &csbi)) return -2;
	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD topLeft = { 0, 0 };
	DWORD written;
	if (!FillConsoleOutputCharacter(*handle, ' ', consoleSize, topLeft, &written)) return -3;
	if (!FillConsoleOutputAttribute(*handle, csbi.wAttributes, consoleSize, topLeft, &written)) return -4;
	if (!SetConsoleCursorPosition(*handle, topLeft)) return -5;
	return 0;
}


int fillRect(HANDLE* handle, Vector2_Int* vect, int width, int height, Glyph* glyph) {
	if (!handle || !vect || !glyph) return -1;
	if (vect->x < 0 || vect->y < 0 || width < 0 || height < 0) return -2;
	int err = 0;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			Vector2_Int v = {vect->x + col, vect->y + row};
			int res = drawGlyph(handle, &v, glyph);
			if (res != 0) err = res;
		}
	}
	return err;
}

// Cursor control
int setCursorVisible(HANDLE* handle, int visible) {
	if (!handle) return -1;
	CONSOLE_CURSOR_INFO cursorInfo;
	if (!GetConsoleCursorInfo(*handle, &cursorInfo)) return -2;
	cursorInfo.bVisible = visible ? TRUE : FALSE;
	if (!SetConsoleCursorInfo(*handle, &cursorInfo)) return -3;
	return 0;
}

int moveCursor(HANDLE* handle, Vector2_Int* vect) {
	if (!handle || !vect) return -1;
	if (vect->x < 0 || vect->y < 0) return -2;
	COORD pos = { (SHORT)vect->x, (SHORT)vect->y };
	if (!SetConsoleCursorPosition(*handle, pos)) return -3;
	return 0;
}

int eraseAtPosition(HANDLE* handle, Vector2_Int* vect) {
	if (!handle || !vect) return -1;
	if (vect->x < 0 || vect->y < 0) return -2;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(*handle, &csbi)) {
		return -3;
	}
	COORD pos = { (SHORT)vect->x, (SHORT)vect->y };
	DWORD written;
	if (!FillConsoleOutputCharacter(*handle, ' ', 1, pos, &written)) return -4;
	if (!FillConsoleOutputAttribute(*handle, csbi.wAttributes, 1, pos, &written)) return -5;
	return 0;
}