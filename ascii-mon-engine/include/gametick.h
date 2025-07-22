/*
*	copyright martin hundrup
*/

/*
* gametick.h contains behavior relating to the central game loop.
*/

#ifndef GAMETICK_H
#define GAMETICK_H

#define TICK_FREQUENCY 20 // Default tick frequency in Hz

#include "ascii-engine.h"

typedef struct game_ticker {
  LARGE_INTEGER freq, start, now, last;
  void (*init)(struct game_ticker* self);
  void (*tick)(struct game_ticker* self); // Called at the end of each frame, sets act
  double (*get_total_elapsed)(struct game_ticker* self); // Seconds since start
  double (*get_delta)(struct game_ticker* self); // Seconds since last frame
  short act; // should act or not
  double lastTick; // Time of the last tick
} Game_Ticker;

void init_game_ticker(Game_Ticker* self);
void tick_game_ticker(Game_Ticker* self);

// number of seconds since init()
double get_total_elapsed(Game_Ticker* self);

// number of seconds since last frame
double get_delta(Game_Ticker* self);

Game_Ticker* new_game_ticker();

#endif