/*
*	copyright Martin Hundrup
*/

/*
*	game.h contains the object structure for the main game handler.
*/

#include "ascii-engine.h"
#include "ticker.h"
#include "input.h"
#include "screen.h"

#ifndef GAME_H
#define GAME_H

typedef struct game {
  Ticker* ticker; // The game ticker for managing game ticks
  Input_Handler* input_handler; // The input handler for user inputs
  Screen* screen; // The screen where the game is drawn

  void (*init)(struct game* self, Transform screenTransform, int tick_frequency); // Initialize the game
  void (*tick_start)(struct game* self); // called at start of each frame
  void (*tick_end)(struct game* self); // called at end of each frame
} Game;

// Creates a new dynamic game instance.
Game* game_new_game();

// Initializes the game instance.
void game_init(Game* self, Transform screenTransform, int tick_frequency);

// Updates the game state for the start of the frame.
void game_tick_start(Game* self);

// Cleans up and draws the game state at the end of the frame.
void game_tick_end(Game* self);

#endif // GAME_H