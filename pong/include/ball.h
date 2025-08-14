/*
*	copyright Martin Hundrup
*/

/*
*	ball.h contains the function prototypes for the ball object.
*/

#ifndef BALL_H
#define BALL_H

#define BALL_GLYPH (Glyph){'o', COLOR_WHITE, COLOR_BLACK}
#define BALL_WIDTH 1
#define BALL_HEIGHT 1
#define BALL_SPEED 1

#include "pong.h"

// creates a new dynamic ball obj.
Object* ball_create(Screen* screen);

// updates the state of a ball obj.
void ball_tick(Object* obj, Game* game);

#endif // BALL_H