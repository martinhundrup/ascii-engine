/*
*	copyright Martin Hundrup
*/

/*
*	pong.c contains the main game logic for the Pong game.
*/

#include "../include/pong.h"
#include "../include/ball.h"
#include "../include/paddle.h"

int title_screen(void) {
  return 0;
}

void play_pong(int num_players) {
Transform screenT = {{0,2},{80, 20}};
	int tick_frequency = 20; // 20 ticks per second

  Game* game = game_new_game();
  game->init(game, screenT, tick_frequency);

	Glyph background = {' ', COLOR_WHITE, COLOR_BLACK};

  // create p1 paddle
  Object* p1 = paddle_create_p1_paddle(game->screen);
  Object* p2 = paddle_create_p2_paddle(game->screen);

  // create ball
  Object* ball = ball_create(game->screen);

  // header stuff
  Screen *header = screen_init((Transform){{0, 1}, {80, 1}}); // Header screen
  Glyph_Str testStr = {
    "ASCII PONG",
    COLOR_BRIGHT_YELLOW,
    COLOR_BLACK
  };

  int gameOver = 0;

  system("cls"); // hard clear the console screen

	do {
		if (game->ticker->act) { // wait for the next tick
			// handle start of tick
			game->tick_start(game);

      // handle the header                           
      screen_empty(header);
      screen_putGlyphStr(header, testStr, (Vector2){0, 0});
      screen_draw(header); // Draw the header
      
      // Print header text
      screen_putGlyphStr(header, testStr, (Vector2){0, 0});

      // Draw the header
      screen_draw(header);

			// detect game quit
			if (input_is_key_pressed(game->input_handler, VK_ESCAPE)) {
				gameOver = 1;
			}

      screen_fill(game->screen, background); // fill the screen with background

      // ** HANDLE PADDLES ** //            
      p1->tick(p1, game);
      p2->tick(p2, game);
      p1->draw(p1, game);
      p2->draw(p2, game);
      // ** END HANDLE PADDLES ** //
			                                      
      // ** HANDLE BALL ** //
      ball->tick(ball, game);
      ball->draw(ball, game);
      // ** END HANDLE BALL ** //

			game->tick_end(game); // handle end of tick
		}
		game->ticker->tick(game->ticker);   
	} while (!gameOver);

  Glyph_Str gameOverStr = {
    "GAME OVER!",
    COLOR_RED,
    COLOR_BLACK
  };

  screen_putGlyphStr(game->screen, gameOverStr, (Vector2){35, 9});
  screen_draw(game->screen);
}