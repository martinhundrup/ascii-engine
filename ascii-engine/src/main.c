/*
*	copyright martin hundrup
*/

/*
*	main.c is the entry point for engine testing.
*	this file should not contain and code critical
*	for use of the engine.
*/

#include "../include/game.h"

int main() {

	system("cls"); // hard clear the console screen

	int tick_frequency = 20; // 20 ticks per second

	Game* game = game_new_game();
	game->init(game, (Vector2_Int){80, 20}, tick_frequency);

	Glyph background = {' ', COLOR_WHITE, COLOR_WHITE};

	Glyph player = {' ', COLOR_WHITE, COLOR_GREEN};
	Vector2_Int v = {0};

	do {
		if (game->ticker->act) { // wait for the next tick
			game->tick_start(game);

			screen_fill(game->screen, background); // fill the screen with background

			// detect game quit
			if (input_is_key_pressed(game->input_handler, VK_ESCAPE)) {
				screen_clear(game->screen);
				printf("Escape key pressed, exiting...\n");
				break;
			}

			screen_fill(game->screen, background); // fill the screen with background

			// player input
			if (input_is_key_down(game->input_handler, 'D')){
				v.x++;
			}
			if (input_is_key_down(game->input_handler, 'A')){
				v.x--;
			}		
			if (input_is_key_down(game->input_handler, 'W')){
				v.y--;
			}		
			if (input_is_key_down(game->input_handler, 'S')){
				v.y++;
			}
			screen_putGlyph(game->screen, player, v);
			
			game->tick_end(game); // end of tick
		}

		game->ticker->tick(game->ticker);
	} while (1); // Loop for 1 second

	printf("total elapsed time: %lf\n", ticker_get_total_elapsed(game->ticker));

	return 0;
}