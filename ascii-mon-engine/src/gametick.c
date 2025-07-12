/*
*	copyright martin hundrup
*/

/*
* gametick.c contains function implementations for gametick.h
*/

#include "../include/gametick.h"

struct game_ticker* new_game_ticker() {
  struct game_ticker* gt = (struct game_ticker*)malloc(sizeof(struct game_ticker));
  gt->init = init_game_ticker;
  gt->tick = tick_game_ticker;
  gt->get_total_elapsed = get_total_elapsed;
  gt->get_delta = get_delta;
  return gt;
}

void init_game_ticker(struct game_ticker* self) {
  QueryPerformanceFrequency(&self->freq);
  QueryPerformanceCounter(&self->start);
  self->now = self->start;
  self->last = self->start;
}

void tick_game_ticker(struct game_ticker* self) {
  self->last = self->now;
  QueryPerformanceCounter(&self->now);
}

double get_total_elapsed(struct game_ticker* self) {
  LONGLONG elapsed = self->now.QuadPart - self->start.QuadPart;
  return (double)elapsed / (double)self->freq.QuadPart;
}

double get_delta(struct game_ticker* self) {
  LONGLONG delta = self->now.QuadPart - self->last.QuadPart;
  return (double)delta / (double)self->freq.QuadPart;
}
