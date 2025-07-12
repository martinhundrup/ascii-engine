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
#include "../include/gametick.h"

int main() {
	int x = 0;
	
	struct game_ticker* gt = new_game_ticker();
	gt->init(gt);
	
	HANDLE* input = configureConsoleInput();

	do {

		WORD key = getInputKeyCode(input);
		if (key != 0) {
			printf("keycode down: %d\n", key);
		}

		if (isKeyDown(input, VK_ESCAPE)) {
			printf("Escape key pressed, exiting...\n");
			break;
		}

		printf("time since last tick: %lf\n", gt->get_delta(gt));
		
		x++;
		gt->tick(gt);
	} while (gt->get_total_elapsed(gt) < RUNTIME); // Loop for 1 second

	printf("tick count: %d\n", x);
	printf("total elapsed time: %lf\n", gt->get_total_elapsed(gt));

	return 0;
}