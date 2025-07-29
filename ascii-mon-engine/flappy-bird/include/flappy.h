/*
*	copyright Martin Hundrup
*/

/*
*	flappy.h contains the main header for the Flappy Bird game.
*/

#ifndef FLAPPY_H
#define FLAPPY_H

#include "../../include/ascii-engine.h"
#include "../../include/input.h"
#include "../../include/gametick.h"
#include "../../include/draw.h"

typedef struct {
  Vector2_Int position;
  Vector2_Int size;
} Transform;

// Returns a random int within the specified range (inclusive).
int flappy_getRandomRange(int min, int max);

#endif // FLAPPY_H