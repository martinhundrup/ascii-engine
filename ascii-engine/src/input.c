/*
*	copyright martin hundrup
*/

/*
*	input.c contains the function definitions for input handling.
*/

#include "../include/input.h"


// Function to initialize input handling
Input_Handler* input_new_input() {
    Input_Handler* handler = (Input_Handler*)malloc(sizeof(Input_Handler));
    if (!handler) return NULL;

    handler->input = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(handler->input, &mode);

    // Disable line input and echo input
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    // Enable window and mouse input so we can use ReadConsoleInput
    mode |= ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;

    SetConsoleMode(handler->input, mode);

    // Zero initialize key state arrays
    for (int i = 0; i < MAX_KEYS; i++) {
        handler->previousKeyStates[i] = 0;
        handler->currentKeyStates[i] = 0;
    }

    handler->tick = input_tick;
    return handler;
}

void input_tick(Input_Handler* handler) {
    for (int i = 0; i < MAX_KEYS; i++) {
        handler->previousKeyStates[i] = handler->currentKeyStates[i];
        handler->currentKeyStates[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }
}

int input_is_key_pressed(Input_Handler* handler, WORD keyCode) {
    if (keyCode >= MAX_KEYS) return 0;
    return handler->currentKeyStates[keyCode] && !handler->previousKeyStates[keyCode];
}

int input_is_key_released(Input_Handler* handler, WORD keyCode) {
    if (keyCode >= MAX_KEYS) return 0;
    return !handler->currentKeyStates[keyCode] && handler->previousKeyStates[keyCode];
}

int input_is_key_down(Input_Handler* handler, WORD keyCode) {
    if (keyCode >= MAX_KEYS) return 0;
    return handler->currentKeyStates[keyCode];
}

// Optionally peek at the current console buffer input
WORD getInputKeyCode(Input_Handler* handler) {
    DWORD eventsRead = 0;
    INPUT_RECORD ir;
    WORD vk = 0;

    if (PeekConsoleInput(handler->input, &ir, 1, &eventsRead) && eventsRead > 0) {
        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
            vk = ir.Event.KeyEvent.wVirtualKeyCode;
        }
        ReadConsoleInput(handler->input, &ir, 1, &eventsRead);
    }

    return vk;
}
