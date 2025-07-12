/*
*	copyright martin hundrup
*/

/*
* gametick.h contains behavior relating to the central game loop.
*/

#ifndef GAMETICK_H
#define GAMETICK_H

#include "ascii-engine.h"

struct game_ticker {
  LARGE_INTEGER freq, start, now, last;
  void (*init)(struct game_ticker* self);
  void (*tick)(struct game_ticker* self); // Called at the end of each frame
  double (*get_total_elapsed)(struct game_ticker* self); // Seconds since start
  double (*get_delta)(struct game_ticker* self); // Seconds since last frame
};

void init_game_ticker(struct game_ticker* self);

void tick_game_ticker(struct game_ticker* self);

// number of seconds since init()
double get_total_elapsed(struct game_ticker* self);

// number of seconds since last frame
double get_delta(struct game_ticker* self);

struct game_ticker* new_game_ticker();

#endif