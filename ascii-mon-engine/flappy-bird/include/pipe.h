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

typedef struct {
    Transform transform; // Position and size of the pipe
    Glyph glyph; // Glyph representing the pipe
} Pipe;

typedef struct {
  Pipe top; // Top pipe
  Pipe bottom; // Bottom pipe
} Pipe_Pair;

// Creates and initializes a new Pipe instance.
Pipe flappy_createPipe(Transform transform, Glyph glyph);

// Draws a pipe to the screen.
int flappy_drawPipe(Screen* screen, Pipe* pipe);

// Creates a pipe that is positioned at the bottom of the screen.
Pipe flappy_createBottomPipe(Screen* screen);

// Creates a pipe that is positioned at the top of the screen.
Pipe flappy_createTopPipe(Screen* screen);

// Creates a random pipe.
Pipe_Pair flappy_createRandomPipePair(Screen* screen);

// Creates a pipe that is positioned opposite the provided pipe.
Pipe flappy_createRepricolPipe(Screen* screen, Pipe* original);

// Moves a pipe pair left by a specified distance.
void flappy_movePairLeft(Pipe_Pair* pair, int distance);

#endif // PIPE_H