/*
*	copyright Martin Hundrup
*/

/*
*	main.c contains the entry point for playing the game.
*/

#include "../include/flappy.h"
#include "../include/pipe.h"
#include "../include/bird.h"

int main() {

  srand(time(NULL)); // Seed the random number generator

  Transform screenT = {{0,2},{80, 20}};
	int tick_frequency = 20; // 20 ticks per second

  Game* game = game_new_game();
  game->init(game, screenT, tick_frequency);

	Glyph background = {'#', COLOR_WHITE, COLOR_BLACK};

  Pipe_Pair* pipes = (Pipe_Pair*)malloc(sizeof(Pipe_Pair) * MAX_PIPES); // can store MAX_PIPES pipes
  byte pipeActive[MAX_PIPES] = {0}; // track active pipes
  int gameOver = 0;
  int score = 0;
  Object* bird = bird_createBird(game->screen); // Create the bird
  
  // header stuff
  Screen *header = screen_init((Transform){{0, 1}, {80, 1}}); // Header screen
  Glyph_Str testStr = {
    "Flappy Bird Clone",
    COLOR_BRIGHT_YELLOW,
    COLOR_BLACK
  };

  system("cls"); // hard clear the console screen

	do {
		if (game->ticker->act) { // wait for the next tick
			// handle start of tick
			game->tick_start(game);

      // handle the header                           
      screen_empty(header);
      sprintf(testStr.str, "Score: %d", score);
      screen_putGlyphStr(header, testStr, (Vector2){0, 0});
      screen_draw(header); // Draw the header
      
      // Print header text
      screen_putGlyphStr(header, testStr, (Vector2){0, 0});

      // Print frame count
      sprintf(testStr.str, "Frame: %d", game->frame_count);
      screen_putGlyphStr(header, testStr, (Vector2){0, 1});

      // Print tick count
      sprintf(testStr.str, "Tick: %d", game->ticker->tick_count);
      screen_putGlyphStr(header, testStr, (Vector2){0, 2});

      // Print score
      sprintf(testStr.str, "Score: %d", score);
      screen_putGlyphStr(header, testStr, (Vector2){0, 3});

      // Draw the header
      screen_draw(header);

			// detect game quit
			if (input_is_key_pressed(game->input_handler, VK_ESCAPE)) {
				gameOver = 1;
			}

      screen_fill(game->screen, background); // fill the screen with background
    
      // *** HANDLE PIPES *** //
      for (int i = 0; i < MAX_PIPES; i++) {
        if (pipeActive[i]) {
          pipe_pair_tick(&pipes[i], game); // Move the pipe pair left
          pipe_draw_pair(&pipes[i], game); // Draw the pipe pair
          // Check if pipe has gone off screen                                                                   
          if (pipes[i].top->transform.position.x < 0) {
            pipeActive[i] = 0; // Deactivate pipe when it goes off screen
            pipe_delete_pair(pipes[i]); // Free the pipe pair
            score++; // Increment score for passing a pipe
          }
        }
      }			
      // generate new pipe every 100 ticks
      if (game->frame_count % 20 == 0) {
        for (int i = 0; i < MAX_PIPES; i++) {
          if (!pipeActive[i]) {
            pipes[i] = pipe_createRandomPipePair(game);
            pipeActive[i] = 1;
            break;
          } 
        }
      }      
      // *** END HANDLE PIPES *** //

      // ** HANDLE BIRD ** //            
      bird->tick(bird, game); // Move the bird based on inputdr
      bird->draw(bird, game); // Draw the bird
      // ** END HANDLE BIRD ** //

      // ** CHECK COLLISION ** //
      for (int i = 0; i < MAX_PIPES; i++) {
        if (pipeActive[i]) {
          if (overlaps(bird->transform, pipes[i].top->transform) || 
              overlaps(bird->transform, pipes[i].bottom->transform)) {
            gameOver = 1;
          }
        }
      }
      // ** END CHECK COLLISION ** //
			                                                               
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

	return 0;
}