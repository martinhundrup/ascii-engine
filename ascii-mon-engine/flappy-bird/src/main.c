/*
*	copyright Martin Hundrup
*/

/*
*	main.c contains the entry point for playing the game.
*/

#include "../include/flappy.h"

int main() {

  printf("Welcome to Flappy Bird!\n");
  return 0;

	int tick_frequency = 20; // 20 ticks per second

	Game_Ticker* gt = new_game_ticker(tick_frequency);
	gt->init(gt);
	
	Input_Handler* ih = configureConsoleInput();
	Screen* screen = screen_init((Vector2_Int){80, 25});

	Glyph background = {' ', COLOR_WHITE, COLOR_WHITE};

	Glyph player = {' ', COLOR_WHITE, COLOR_GREEN};
	Vector2_Int v = {0};

	do {
		if (gt->act) { // wait for the next tick
			// handle start of tick
			ih->tick(ih); // get input
			screen_empty(screen); // refresh the screen buffer

			// detect game quit
			if (isKeyPressed(ih, VK_ESCAPE)) {
				screen_clear(screen);
				printf("Escape key pressed, exiting...\n");
				break;
			}

			screen_fill(screen, background); // fill the screen with background

			// player input
			if (isKeyDown(ih, 'D')){
				v.x++;
			}
			if (isKeyDown(ih, 'A')){
				v.x--;
			}		
			if (isKeyDown(ih, 'W')){
				v.y--;
			}		
			if (isKeyDown(ih, 'S')){
				v.y++;
			}
			screen_putGlyph(screen, player, v);
			
			// draw screen as last step in the frame
			screen_draw(screen);
		}
		gt->tick(gt);
	} while (1); // Loop for 1 second

	printf("total elapsed time: %lf\n", gt->get_total_elapsed(gt));

	return 0;
}