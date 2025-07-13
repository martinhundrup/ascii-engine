/*
*	copyright martin hundrup
*/

/*
* gametick.c contains function implementations for gametick.h
*/

#include "../include/gametick.h"

Game_Ticker* new_game_ticker() {
  Game_Ticker* gt = (Game_Ticker*)malloc(sizeof(Game_Ticker));
  gt->init = init_game_ticker;
  gt->tick = tick_game_ticker;
  gt->get_total_elapsed = get_total_elapsed;
  gt->get_delta = get_delta;
  return gt;
}

void init_game_ticker(Game_Ticker* self) {
  QueryPerformanceFrequency(&self->freq);
  QueryPerformanceCounter(&self->start);
  self->now = self->start;
  self->last = self->start;
}

void tick_game_ticker(Game_Ticker* self) {
  self->last = self->now;
  QueryPerformanceCounter(&self->now);
}

double get_total_elapsed(Game_Ticker* self) {
  LONGLONG elapsed = self->now.QuadPart - self->start.QuadPart;
  return (double)elapsed / (double)self->freq.QuadPart;
}

double get_delta(Game_Ticker* self) {
  LONGLONG delta = self->now.QuadPart - self->last.QuadPart;
  return (double)delta / (double)self->freq.QuadPart;
}
