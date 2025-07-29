/*
*	copyright Martin Hundrup
*/

/*
*	bird.h contains the headers for the bird in the Flappy Bird game.
*/

#ifndef BIRD_H
#define BIRD_H

#define BIRD_WIDTH 3
#define BIRD_HEIGHT 3
#define BIRD_GLYPH (Glyph){'O', COLOR_YELLOW, COLOR_BLACK}

#include "../include/flappy.h"

typedef struct {
    Vector2_Int position; // Position of the bird
    Vector2_Int size; // Size of the bird
    Glyph glyph; // Glyph representing the bird
} Bird;

#endif // BIRD_H