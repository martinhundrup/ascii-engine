/*
*	copyright Martin Hundrup
*/

/*
*	ball.c contains the implementation of the ball object for the Pong game.
*/

#include "../include/ball.h"


// creates a new dynamic ball obj.
Object* ball_create(Screen* screen){
  Object* b = object_create_game_object(
    (Transform){{screen->transform.size.x / 2, screen->transform.size.y / 2},
    {BALL_WIDTH, BALL_HEIGHT}}, 
    BALL_GLYPH);
  b->tick = ball_tick;

  // coin flip for starting direction
  if (getRandomRange(0, 1))
    b->velocity = (Vector2_F){-BALL_SPEED, 0};
  else
    b->velocity = (Vector2_F){BALL_SPEED, 0};
  return b;
}

// updates the state of a ball obj.
void ball_tick(Object* obj, Game* game) {
  Vector2 pos = obj->transform.position;

  // update ball position
  obj->transform.position.y += obj->velocity.y;
  obj->transform.position.x += obj->velocity.x;

  // make sure it is still in bounds
  if (!inside(obj->transform, (Transform){{0,0}, game->screen->transform.size})) {
    obj->transform.position = pos; // put it back

    // determine which velocity to reverse
    if (obj->transform.position.x == 0 || obj->transform.position.x == game->screen->transform.size.x){
      obj->velocity.x *= -1;
    } else {
      obj->velocity.y *= -1;
    }

    // update ball position again
    obj->transform.position.y += obj->velocity.y;
    obj->transform.position.x += obj->velocity.x;
  }
}