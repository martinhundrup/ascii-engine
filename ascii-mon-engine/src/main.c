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

int main() {
	
	Game_Ticker* gt = new_game_ticker();
	gt->init(gt);
	
	Input_Handler* ih = configureConsoleInput();
	HANDLE* output = configureDrawSystem();
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

	printf("total elapsed time: %lf\n", gt->get_total_elapsed(gt));

	// Vector2_Int size = {10, 5};
	// g.symbol = ' ';
	// fillRect(output, &v, &size, &g);

	return 0;
}