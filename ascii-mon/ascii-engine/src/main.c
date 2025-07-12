/*
*	copyright martin hundrup
*/

/*
*	main.c is the entry point for engine testing.
*	this file should not contain and code critical
*	for use of the engine.
*/

#define TICK_MS 5
#define RUNTIME 10

#include "../include/ascii-engine.h"
#include "../include/input.h"

int main() {
	int x = 0;

	LARGE_INTEGER freq, start, now;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	
	struct InputHandler* input = configureConsoleInput();
	double elapsed = 0.0;

	do {

		WORD key = getInputKeyCode(input);
		if (key != 0) {
			printf("keycode downd: %d\n", key);
		}

		if (isKeyDown(input, VK_ESCAPE)) {
			printf("Escape key pressed, exiting...\n");
			break;
		}
		
		x++;
		QueryPerformanceCounter(&now);
		elapsed = (double)(now.QuadPart - start.QuadPart) * 1000.0 / (double)freq.QuadPart;
	} while (elapsed < 1000.0 * RUNTIME); // Loop for 1 second

	printf("tick count: %d\n", x);

	return 0;
}