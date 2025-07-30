/*
*	copyright martin hundrup
*/

/*
* ticker.c contains function implementations for ticker.h
*/

#include "../include/ticker.h"

Ticker* ticker_create_ticker(int freq) {
  Ticker* gt = (Ticker*)malloc(sizeof(Ticker));
  gt->init = ticker_init;
  gt->tick = ticker_tick;
  gt->get_total_elapsed = ticker_get_total_elapsed;
  gt->get_delta = ticker_get_delta;
  gt->act = 0;
  gt->lastTick = 0;
  gt->tick_frequency = freq;
  gt->tick_count = 0;
  return gt;
}

void ticker_init(Ticker* self) {
  QueryPerformanceFrequency(&self->freq);
  QueryPerformanceCounter(&self->start);
  self->now = self->start;
  self->last = self->start;
}

void ticker_tick(Ticker* self) {
  self->last = self->now;
  QueryPerformanceCounter(&self->now);

  self->act = 0;
  double elapsed = ticker_get_total_elapsed(self);
  if (elapsed - self->lastTick >= 1.0 / self->tick_frequency) {
    self->act = 1; // Set act to true if enough time has passed
    self->lastTick = elapsed;
    self->tick_count++;
  }
}

double ticker_get_total_elapsed(Ticker* self) {
  LONGLONG elapsed = self->now.QuadPart - self->start.QuadPart;
  return (double)elapsed / (double)self->freq.QuadPart;
}

double ticker_get_delta(Ticker* self) {
  LONGLONG delta = self->now.QuadPart - self->last.QuadPart;
  return (double)delta / (double)self->freq.QuadPart;
}
