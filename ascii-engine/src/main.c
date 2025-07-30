// /*
// *	copyright martin hundrup
// */

// /*
// *	main.c is the entry point for engine testing.
// *	this file should not contain and code critical
// *	for use of the engine.
// */

// #include "../include/object.h"

// int main() {

// 	system("cls"); // hard clear the console screen

// 	int tick_frequency = 20; // 20 ticks per second
// 	Transform screenTransform = {{10, 0}, {80, 20}}; // {position, size}

// 	Game* game = game_new_game();
// 	game->init(game, screenTransform, tick_frequency);

// 	Glyph background = {' ', COLOR_WHITE, COLOR_WHITE};

// 	Object* playerObject = object_create_game_object(
// 		(Transform){{1, 1}, {1, 1}}, // {position, size}
// 		(Glyph){' ', COLOR_WHITE, COLOR_GREEN}
// 	);
// 	playerObject->init(playerObject, game); // Initialize the player object

// 	Object* enemyObject = object_create_game_object(
// 		(Transform){{10, 10}, {2, 2}}, // {position, size}
// 		(Glyph){'E', COLOR_WHITE, COLOR_RED}
// 	);
// 	enemyObject->init(enemyObject, game); // Initialize the enemy object

// 	do {
// 		if (game->ticker->act) { // wait for the next tick
// 			game->tick_start(game);

// 			// detect game quit
// 			if (input_is_key_pressed(game->input_handler, VK_ESCAPE)) {
// 				screen_clear(game->screen);
// 				printf("Escape key pressed, exiting...\n");
// 				break;
// 			}

// 			// detect game loss
// 			if (inside(playerObject->transform, enemyObject->transform)) {
// 				screen_clear(game->screen);
// 				printf("YOU LOSE!\n");
// 				break;
// 			}

// 			screen_fill(game->screen, background); // fill the screen with background
// 			//screen_fillRect(game->screen, (Transform){{0, 0}, {2,2}}, background); // fill the screen with background

// 			// player input
// 			if (input_is_key_down(game->input_handler, 'D')){
// 				playerObject->transform.position.x++;
// 			}
// 			if (input_is_key_down(game->input_handler, 'A')){
// 				playerObject->transform.position.x--;
// 			}		
// 			if (input_is_key_down(game->input_handler, 'W')){
// 				playerObject->transform.position.y--;
// 			}		
// 			if (input_is_key_down(game->input_handler, 'S')){
// 				playerObject->transform.position.y++;
// 			}
// 			playerObject->draw(playerObject, game); // draw the player object

// 			enemyObject->draw(enemyObject, game); // draw the enemy object
			

// 			game->tick_end(game); // end of tick, draws the screen
// 		}

// 		game->ticker->tick(game->ticker);
// 	} while (1); // Loop for 1 second

// 	printf("total elapsed time: %lf\n", ticker_get_total_elapsed(game->ticker));

// 	return 0;
// }