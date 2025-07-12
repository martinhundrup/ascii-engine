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

HANDLE* configureConsoleInput();

WORD getInputKeyCode(HANDLE* inputHandler);

int isKeyDown(HANDLE* inputHandler, WORD keyCode);

#endif