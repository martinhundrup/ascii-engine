/*
*	copyright martin hundrup
*/

/*
*	input.c contains the function definitions for input handling.
*/

#include "../include/input.h"

// Function to initialize input handling
struct InputHandler* configureConsoleInput() {
    
	struct InputHandler* inputHandler = (struct InputHandler*)malloc(sizeof(struct InputHandler));

	for (int i = 0; i < 256; i++) {
		inputHandler->keys[i].keyCode = i;
		inputHandler->keys[i].isDown = 0;
	}

	inputHandler->tick = tick_inputHandler;
    inputHandler->hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    // Get current input mode
    GetConsoleMode(inputHandler->hInput, &mode);

    // Disable line input and echo input
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    // Enable window and mouse input so we can use ReadConsoleInput
    mode |= ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;

    SetConsoleMode(inputHandler->hInput, mode);
	return inputHandler;
}

WORD getInputKeyCode(struct InputHandler* inputHandler) {
    DWORD eventsRead = 0;
    INPUT_RECORD ir;
	WORD vk = 0;
    struct InputKey* key = NULL;
    // Peek instead of Read
    if (PeekConsoleInput(inputHandler->hInput, &ir, 1, &eventsRead) && eventsRead > 0) {
        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
           vk = ir.Event.KeyEvent.wVirtualKeyCode;
           key = &inputHandler->keys[vk];
           key->isDown = 1;
        }
        // Remove the event from the buffer
        ReadConsoleInput(inputHandler->hInput, &ir, 1, &eventsRead);
    }

    return vk;
}


void tick_inputHandler(struct InputHandler* inputHandler) {
	struct InputKey* key;
    for (int i = 0; i < 256; i++) {
        key = &inputHandler->keys[i];
		key->isDown = 0;
    }
}
