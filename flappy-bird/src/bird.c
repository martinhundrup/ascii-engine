/*
*	copyright Martin Hundrup
*/

/*
*	bird.c contains function implementations for bird.h 
*/

#include "../include/bird.h"

Object* bird_createBird(Screen* screen) {
  Transform t = (Transform){{BIRD_X_POS, screen->transform.size.y / 2},{BIRD_WIDTH, BIRD_HEIGHT}};
  Object* bird = object_create_game_object(t, BIRD_GLYPH);
  bird->velocity = (Vector2_F){0.0, -BIRD_JUMP_FORCE}; // Initial velocity is a jump
  bird->tick = bird_tick; // Assign the tick function
  return bird;
}

// Moves the bird based on input.
void bird_tick(Object* bird, Game* game) {

  // first handle gravity
  bird->velocity.y += BIRD_GRAVITY; // Apply gravity to the bird's velocity

  // then handle jump
  if (input_is_key_pressed(game->input_handler, VK_SPACE)) {
    bird->velocity.y = -BIRD_JUMP_FORCE; // Apply jump force
  }

  // update bird position
  bird->transform.position.y += bird->velocity.y;

  // simple ground collision
  if (!inside(bird->transform, (Transform){{0,0}, game->screen->transform.size})) {
    bird->velocity.y = 0; // Stop moving
  }
}

