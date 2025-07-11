/*
*	copyright martin hundrup
*/

/*
*	input.h contains functionality for handling user input.
*	All user input must not block the main thread and not be
*	displayed to the terminal.
*/

#ifndef INPUT_H
#define INPUT_H

#include "ascii-engine.h"

struct InputKey {
	WORD keyCode; // Virtual key code
	short isDown; // Key state (pressed or released)
};

struct InputHandler {
	HANDLE hInput; // Handle to the console input
	struct InputKey keys[256]; // Array to store key states
	void (*tick)(struct InputHandler* inputHandler); // Function pointer for tick function
};

enum InputKeyType {
	LEFT_ARROW,
	RIGHT_ARROW,
	UP_ARROW,
	DOWN_ARROW,
};

struct InputHandler* configureConsoleInput();

WORD getInputKeyCode(struct InputHandler* inputHandler);

void tick_inputHandler(struct InputHandler* inputHandler);

#endif