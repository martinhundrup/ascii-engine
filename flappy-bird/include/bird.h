/*
*	copyright Martin Hundrup
*/

/*
*	bird.h contains the headers for the bird in the Flappy Bird game.
*/

#ifndef BIRD_H
#define BIRD_H

#define BIRD_WIDTH 4
#define BIRD_HEIGHT 2
#define BIRD_GLYPH (Glyph){' ', COLOR_YELLOW, COLOR_YELLOW}
#define BIRD_X_POS 5 // x position of the bird

// bird physics
#define BIRD_GRAVITY 0.2f // Gravity effect on the bird
#define BIRD_JUMP_FORCE 1.0f // Force applied when the bird jumps

#include "../include/flappy.h"

// Creates and initializes a new dynamic Bird instance.
Object* bird_createBird(Screen* screen);

// Moves the bird based on input.
void bird_tick(Object* bird, Game* game);

#endif // BIRD_H