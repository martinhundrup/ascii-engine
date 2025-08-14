/*
*	copyright Martin Hundrup
*/

/*
*	paddle.c contains the implementation of the paddle object for the Pong game.
*/

#include "../include/paddle.h"

Object* paddle_create_p1_paddle(Screen* screen) {
  Object* p = object_create_game_object(
    (Transform){{PADDLE_X_POS,screen->transform.size.y / 2}, {PADDLE_WIDTH, PADDLE_HEIGHT}},PADDLE_GLYPH);
  p->tick = paddle_p1_tick;
  return p;
}

void paddle_p1_tick(Object* obj, Game* game) {
  Vector2 original_pos = obj->transform.position;
  if (input_is_key_down(game->input_handler, 'W')){
    obj->transform.position.y--;
  }
  else if (input_is_key_down(game->input_handler, 'S')){
    obj->transform.position.y++;
  }
  // make sure it is still in bounds
  if (!inside(obj->transform, (Transform){{0,0}, game->screen->transform.size})) {
    obj->transform.position = original_pos; // put it back
  }
}

Object* paddle_create_p2_paddle(Screen* screen) {
  Object* p = object_create_game_object((Transform){{screen->transform.size.x - PADDLE_X_POS, 
    screen->transform.size.y / 2},{PADDLE_WIDTH, PADDLE_HEIGHT}}, PADDLE_GLYPH);
  p->tick = paddle_p2_tick;
  return p;
}

void paddle_p2_tick(Object* obj, Game* game){
  Vector2 original_pos = obj->transform.position;
  if (input_is_key_down(game->input_handler, VK_UP)){
    obj->transform.position.y--;
  }
  else if (input_is_key_down(game->input_handler, VK_DOWN)){
    obj->transform.position.y++;
  }
  // make sure it is still in bounds
  if (!inside(obj->transform, (Transform){{0,0}, game->screen->transform.size})) {
    obj->transform.position = original_pos; // put it back
  }
}

Object* paddle_create_com1_paddle(Screen* screen) {
  Object* p = object_create_game_object((Transform){{PADDLE_X_POS,screen->transform.size.y / 2}, {PADDLE_WIDTH, PADDLE_HEIGHT}}, PADDLE_GLYPH);
  p->tick = paddle_com1_tick;
  return p;
}

void paddle_com1_tick(Object* obj, Game* game){

}

Object* paddle_create_com2_paddle(Screen* screen) {
  Object* p = object_create_game_object((Transform){{screen->transform.size.x - PADDLE_X_POS, screen->transform.size.y / 2},
    {PADDLE_WIDTH, PADDLE_HEIGHT}}, PADDLE_GLYPH);
  p->tick = paddle_com2_tick;
  return p;
}

void paddle_com2_tick(Object* obj, Game* game){

}

void paddle_draw(Object* obj, Game* game) {

}