/*
*	copyright Martin Hundrup
*/

/*
*	flappy.h contains the main header for the Flappy Bird game.
*/

#ifndef PIPE_H
#define PIPE_H

#define MAX_PIPES 10
#define PIPE_WIDTH 5
#define PIPE_HEIGHT_MIN 3
#define PIPE_HEIGHT_MAX 6
#define PIPE_GLYPH (Glyph){' ', COLOR_GREEN, COLOR_GREEN}
#define PIPE_DISTANCE 10 // Distance between pipes

#include "../include/flappy.h"

// pipes are dynamic game object
// pipe pairs are not (we can copy 2 pointers it's fine)
typedef struct {
  Object* top; // Top pipe
  Object* bottom; // Bottom pipe
} Pipe_Pair;

// Creates a new dynamic pipe object with the specified transform and glyph.
Object* pipe_create_pipe(Transform t, Glyph g);

// Creates a new dynamic pipe pair
Pipe_Pair pipe_create_pair(Game* game);

// Creates a pipe that is positioned at the bottom of the screen.
Object* pipe_createBottomPipe(Game* game);

// Creates a pipe that is positioned at the top of the screen.
Object* pipe_createTopPipe(Game* game);

// Creates a random pipe.
Pipe_Pair pipe_createRandomPipePair(Game* game);

// Creates a pipe that is positioned opposite the provided pipe.
Object* flappy_createRepricolPipe(Game* game, Object* original);

// Moves a pipe pair left
void pipe_pair_tick(Pipe_Pair* pair, Game* game);

// Draws a pipe pair on the screen.
void pipe_draw_pair(Pipe_Pair* pair, Game* game);

// Moves a pipe left
void pipe_tick(Object* pair, Game* game);

// frees a pipe pair
void pipe_delete_pair(Pipe_Pair pair);

#endif // PIPE_H