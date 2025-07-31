/*
*	copyright martin hundrup
*/

/*
* ticker.h contains behavior relating to the central game loop.
*/

#ifndef TICKER_H
#define TICKER_H

#include "ascii-engine.h"

typedef struct ticker {
  LARGE_INTEGER freq, start, now, last;
  void (*init)(struct ticker* self);
  void (*tick)(struct ticker* self); // Called at the end of each frame, sets act
  double (*get_total_elapsed)(struct ticker* self); // Seconds since start
  double (*get_delta)(struct ticker* self); // Seconds since last frame
  short act; // should act or not
  double lastTick; // Time of the last tick
  int tick_frequency; // Frequency of ticks in Hz
  int tick_count; // Number of ticks since start
} Ticker;

// initializes the ticker instance.
void ticker_init(Ticker* self);

// ticks the ticker, updates the time and sets act if enough time has passed.
void ticker_tick(Ticker* self);

// number of seconds since init()
double ticker_get_total_elapsed(Ticker* self);

// number of seconds since last frame
double ticker_get_delta(Ticker* self);

// creates a new ticker instance.
Ticker* ticker_create_ticker();

#endif // TICKER_H