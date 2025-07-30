/*
*	copyright martin hundrup
*/

/*
*	game.c contains the function impelementations for the main game struct.
*/

#include "../include/game.h"

Game* game_new_game() {
  Game* game = (Game*)malloc(sizeof(Game));
  // set methods
  game->init = game_init;
  game->tick_start = game_tick_start;
  game->tick_end = game_tick_end;
  return game;
}

void game_init(Game* self, Transform screenTransform, int tick_frequency) {
  self->ticker = ticker_create_ticker(tick_frequency);
  self->ticker->init(self->ticker);
  
  self->input_handler = input_new_input();
  self->screen = screen_init(screenTransform);

  self->input_handler = input_new_input();
}

void game_tick_start(Game* self) {
  self->input_handler->tick(self->input_handler); // Get input
  screen_empty(self->screen); // Clear the screen buffer
}

void game_tick_end(Game* self) {
  // Draw the screen as the last step in the frame
  screen_draw(self->screen);
  self->frame_count++;
}