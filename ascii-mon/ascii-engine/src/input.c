/*
*	copyright martin hundrup
*/

/*
*	input.c contains the function definitions for input handling.
*/

#include "../include/input.h"

// Function to initialize input handling
HANDLE* configureConsoleInput() {
    
	HANDLE* inputHandler = (HANDLE*)malloc(sizeof(HANDLE));

    inputHandler = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    // Get current input mode
    GetConsoleMode(inputHandler, &mode);

    // Disable line input and echo input
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    // Enable window and mouse input so we can use ReadConsoleInput
    mode |= ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;

    SetConsoleMode(inputHandler, mode);
	return inputHandler;
}

WORD getInputKeyCode(HANDLE* inputHandler) {
    DWORD eventsRead = 0;
    INPUT_RECORD ir;
	WORD vk = 0;
    struct InputKey* key = NULL;
    // Peek instead of Read
    if (PeekConsoleInput(inputHandler, &ir, 1, &eventsRead) && eventsRead > 0) {
        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
           vk = ir.Event.KeyEvent.wVirtualKeyCode;
        }
        // Remove the event from the buffer
        ReadConsoleInput(inputHandler, &ir, 1, &eventsRead);
    }

    return vk;
}

int isKeyDown(struct InputHandler* inputHandler, WORD keyCode) {
    // Check if the key is currently pressed down
    return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
}
