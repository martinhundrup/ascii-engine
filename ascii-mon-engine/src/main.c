/*
*	copyright martin hundrup
*/

/*
*	main.c is the entry point for engine testing.
*	this file should not contain and code critical
*	for use of the engine.
*/

#include "../include/ascii-engine.h"
#include "../include/input.h"
#include "../include/gametick.h"
#include "../include/draw.h"
#include "../include/p2p.h"

int game_test(){
	Game_Ticker* gt = new_game_ticker();
	gt->init(gt);
	
	Input_Handler* ih = configureConsoleInput();
	HANDLE* output = configureDrawSystem();
	clearScreen(output);
	setCursorVisible(output, 0); // hide cursor

	// Glyph background = {' ', COLOR_WHITE, COLOR_WHITE};
	// Vector2_Int backgroundSize = {80, 25};

	Glyph player = {' ', COLOR_WHITE, COLOR_GREEN};
	Vector2_Int v = {0};

	do {

		if (gt->act) {

			//fillRect(output, &(Vector2_Int){0, 0}, &backgroundSize, &background);

			ih->tick(ih);

			if (isKeyPressed(ih, VK_ESCAPE)) {
				printf("Escape key pressed, exiting...\n");
				break;
			}

			if (isKeyDown(ih, 'D')){
				eraseAtPosition(output, &v);
				v.x++;
			}
			if (isKeyDown(ih, 'A')){
				eraseAtPosition(output, &v);
				v.x--;
			}		
			if (isKeyDown(ih, 'W')){
				eraseAtPosition(output, &v);
				v.y--;
			}		
			if (isKeyDown(ih, 'S')){
				eraseAtPosition(output, &v);
				v.y++;
			}		


			drawGlyph(output, &v, &player);
		}
		gt->tick(gt);
	} while (1); // Loop for 1 second

	clearScreen(output);
	printf("total elapsed time: %lf\n", gt->get_total_elapsed(gt));

	// Vector2_Int size = {10, 5};
	// g.symbol = ' ';
	// fillRect(output, &v, &size, &g);

	return 0;
}

int main(int arc	, char* argv[]) {

	if (!P2P_Init("../lib/p2p.dll")) {
		printf("P2P failed to load.\n");
		return 1;
  }
	
	if (strcmp(argv[1], "game") == 0) {
		return game_test();
	} else if (strcmp(argv[1], "client") == 0) {
		return client_test(argv[2]);
	} else if (strcmp(argv[1], "server") == 0) {
		return server_test();
	} else {
		printf("Usage: %s [game|client|server]\n", argv[0]);
		return 1;
	}

	return 0;
}