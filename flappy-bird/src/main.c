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

  Vector2_Int screenSize = {80, 20};
	int tick_frequency = 20; // 20 ticks per second

	Ticker* gt = ticker_create_ticker(tick_frequency);
	gt->init(gt);
	
	Input_Handler* ih = input_new_input();
	Screen* screen = screen_init(screenSize);

	Glyph background = {'#', COLOR_WHITE, COLOR_BLACK};

  Pipe_Pair* pipes = (Pipe_Pair*)malloc(sizeof(Pipe_Pair) * MAX_PIPES); // can store MAX_PIPES pipes
  byte pipeActive[MAX_PIPES] = {0}; // track active pipes

  Bird* bird = bird_createBird(screen); // Create the bird

  int game_tick_counter = 0; // Counter to track game ticks

	do {
		if (gt->act) { // wait for the next tick
			// handle start of tick
			ih->tick(ih); // get input
			screen_empty(screen); // refresh the screen buffer

			// detect game quit
			if (input_is_key_pressed(ih, VK_ESCAPE)) {
				screen_clear(screen);
				printf("Escape key pressed, exiting...\n");
				break;
			}

      screen_fill(screen, background); // fill the screen with background
    
      // *** HANDLE PIPES *** //
      for (int i = 0; i < MAX_PIPES; i++) {
        if (pipeActive[i]) {
          flappy_movePairLeft(&pipes[i], 1); // Move pipes left by 1 character
          flappy_drawPipe(screen, &pipes[i].top);
          flappy_drawPipe(screen, &pipes[i].bottom);
        }

        if (pipes[i].top.transform.position.x < 0) {
          pipeActive[i] = 0; // Deactivate pipe when it goes off screen
        }
      }			
      // generate new pipe every 100 ticks
      if (game_tick_counter % 20 == 0) {
        for (int i = 0; i < MAX_PIPES; i++) {
          if (!pipeActive[i]) {
            pipes[i] = flappy_createRandomPipePair(screen);
            pipeActive[i] = 1;
            break;
          } 
        }
      } 
      // *** END HANDLE PIPES *** //

      // ** HANDLE BIRD ** //

      bird_tick(bird, screen, ih); // Move the bird based on input
      bird_draw(screen, bird); // Draw the bird

      // ** END HANDLE BIRD ** //
			                                                               
			// draw screen as last step in the frame
			screen_draw(screen);
      game_tick_counter++;
		}
		gt->tick(gt);   
	} while (1); // Loop for 1 second

	printf("total elapsed time: %lf\n", gt->ticker_get_total_elapsed(gt));

	return 0;
}