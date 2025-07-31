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

// creates and initializes a new input handler instance.
Input_Handler* input_new_input();

void input_tick(Input_Handler* handler);
int input_is_key_pressed(Input_Handler* handler, WORD keyCode);
int input_is_key_released(Input_Handler* handler, WORD keyCode);
int input_is_key_down(Input_Handler* handler, WORD keyCode);

WORD getInputKeyCode(Input_Handler* handler);

#endif