/*
*	copyright Martin Hundrup
*/

/*
*	flappy.h contains the main header for the Flappy Bird game.
*/

#ifndef FLAPPY_H
#define FLAPPY_H

#include "../../ascii-engine/include/ascii-engine.h"
#include "../../ascii-engine/include/input.h"
#include "../../ascii-engine/include/gametick.h"
#include "../../ascii-engine/include/draw.h"
#include "../../ascii-engine/include/gameobject.h"



// Returns a random int within the specified range (inclusive).
int flappy_getRandomRange(int min, int max);

#endif // FLAPPY_H