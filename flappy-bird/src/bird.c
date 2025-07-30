/*
*	copyright Martin Hundrup
*/

/*
*	bird.c contains function implementations for bird.h 
*/

#include "../include/bird.h"

Bird* bird_createBird(Screen* screen) {
    Bird* bird = (Bird*)malloc(sizeof(Bird));
    bird->transform.position = (Vector2_Int){BIRD_X_POS, screen->_size.y / 2};
    bird->transform.size = (Vector2_Int){BIRD_WIDTH, BIRD_HEIGHT};
    bird->glyph = BIRD_GLYPH;
    bird->velocity = (Vector2_F){0.0, -BIRD_JUMP_FORCE}; // Initial velocity is a jump
    return bird;
}

// Draws the bird to the screen.
int bird_draw(Screen* screen, Bird* bird) {
  if (!screen || !bird) return -1;
  return screen_fillRect(screen, bird->transform.position, bird->transform.size, bird->glyph);
}

// Moves the bird based on input.
void bird_tick(Bird* bird, Screen* screen, Input_Handler* ih) {

  // first handle gravity
  bird->velocity.y += BIRD_GRAVITY; // Apply gravity to the bird's velocity

  // then handle jump
  if (input_is_key_pressed(ih, VK_SPACE)) {
    bird->velocity.y = -BIRD_JUMP_FORCE; // Apply jump force
  }

  // update bird position
  bird->transform.position.y += bird->velocity.y;

  // simple ground collision
  if (bird->transform.position.y + bird->transform.size.y > screen->_size.y) {
    bird->transform.position.y = screen->_size.y - bird->transform.size.y;
    bird->velocity.y = 0; // Stop falling
  }
}

