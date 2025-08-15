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

// collision handler.
void ball_collision(Object* obj, Game* game, Object* left_paddle, Object* right_paddle);

#endif // BALL_H