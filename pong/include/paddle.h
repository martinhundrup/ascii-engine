/*
*	copyright Martin Hundrup
*/

/*
*	paddle.h contains the function prototypes for the paddle object.
*/

#ifndef PADDLE_H
#define PADDLE_H

#define PADDLE_WIDTH 1
#define PADDLE_HEIGHT 5
#define PADDLE_GLYPH (Glyph){'#', COLOR_WHITE, COLOR_BLACK}
#define PADDLE_X_POS 2 // distance from edge of screen

#include "pong.h"

// creates a new p1 paddle.
Object* paddle_create_p1_paddle(Screen* screen);

// updates p1 paddle state.
void paddle_p1_tick(Object* obj, Game* game);

// creates a new p2 paddle.
Object* paddle_create_p2_paddle(Screen* screen);

// updates p2 paddle state.
void paddle_p2_tick(Object* obj, Game* game);

// creates a p1 computer paddle.
Object* paddle_create_com1_paddle(Screen* screen);

// updates p1 computer paddle state.
void paddle_com1_tick(Object* obj, Game* game);

// creates a p2 computer paddle.
Object* paddle_create_com2_paddle(Screen* screen);

// updates p2 computer paddle state.
void paddle_com2_tick(Object* obj, Game* game);

// draws a paddle to the screen.
void paddle_draw(Object* obj, Game* game);

#endif // PADDLE_H