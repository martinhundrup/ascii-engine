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

#define MAX_KEYS 256

#include "ascii-engine.h"

typedef struct input_handler {
    HANDLE* input;
    BYTE previousKeyStates[MAX_KEYS];
    BYTE currentKeyStates[MAX_KEYS];
    void (*tick)(struct input_handler* self);
} Input_Handler;

Input_Handler* configureConsoleInput();

void updateInputStates(Input_Handler* handler);
int isKeyPressed(Input_Handler* handler, WORD keyCode);
int isKeyReleased(Input_Handler* handler, WORD keyCode);
int isKeyDown(Input_Handler* handler, WORD keyCode);

WORD getInputKeyCode(Input_Handler* handler);

#endif