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

	Glyph g = {'t', COLOR_WHITE, COLOR_GREEN};
	Vector2_Int v = {0};

	do {
		ih->tick(ih);

		if (isKeyPressed(ih, VK_ESCAPE)) {
			printf("Escape key pressed, exiting...\n");
			break;
		}

		if (isKeyPressed(ih, 'D')){
			eraseAtPosition(output, &v);
			v.x++;
			drawGlyph(output, &v, &g);
		}
		if (isKeyPressed(ih, 'A')){
			eraseAtPosition(output, &v);
			v.x--;
			drawGlyph(output, &v, &g);
		}		
		if (isKeyPressed(ih, 'W')){
			eraseAtPosition(output, &v);
			v.y--;
			drawGlyph(output, &v, &g);
		}		
		if (isKeyPressed(ih, 'S')){
			eraseAtPosition(output, &v);
			v.y++;
			drawGlyph(output, &v, &g);
		}		

		gt->tick(gt);
	} while (1); // Loop for 1 second

	printf("total elapsed time: %lf\n", gt->get_total_elapsed(gt));

	// Vector2_Int size = {10, 5};
	// g.symbol = ' ';
	// fillRect(output, &v, &size, &g);

	return 0;
}