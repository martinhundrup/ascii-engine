/*
*	copyright Martin Hundrup
*/

/*
*	pipe.c contains function implementations for pipe.h 
*/

#include "../include/pipe.h"

Object* pipe_create_pipe(Transform t, Glyph g){
  Object* pipe = object_create_game_object(t, g);
  pipe->tick = pipe_tick; // Assign the tick function
  return pipe;
}

Pipe_Pair pipe_create_pair(Game* game) {
    Pipe_Pair pair = {0};
    pair.top = pipe_createTopPipe(game);
    pair.bottom = flappy_createRepricolPipe(game, pair.top);
    return pair;
}

// pipe widths are fixed at PIPE_WIDTH characters wide
// pipe heights are random between PIPE_HEIGHT_MIN and PIPE_HEIGHT_MAX characters

Object* pipe_createBottomPipe(Game* game){
  Vector2 size = {PIPE_WIDTH, getRandomRange(PIPE_HEIGHT_MIN, PIPE_HEIGHT_MAX)};
  Vector2 position = {game->screen->transform.size.x - size.x, game->screen->transform.size.y - size.y};
  return pipe_create_pipe((Transform){position, size}, PIPE_GLYPH);
}

Object* pipe_createTopPipe(Game* game){
  Vector2 size = {PIPE_WIDTH, getRandomRange(PIPE_HEIGHT_MIN, PIPE_HEIGHT_MAX)};
  Vector2 position = {game->screen->transform.size.x - size.x, 0};
  return pipe_create_pipe((Transform){position, size}, PIPE_GLYPH);
}

Pipe_Pair pipe_createRandomPipePair(Game* game) {
    Pipe_Pair pair;
    pair.top = pipe_createTopPipe(game);
    pair.bottom = flappy_createRepricolPipe(game, pair.top);
    return pair;
}

Object* flappy_createRepricolPipe(Game* game, Object* original) {
  Vector2 position = {original->transform.position.x, 0}; // Start at the same x position
  Vector2 size = original->transform.size;
  size.y = game->screen->transform.size.y - (original->transform.size.y + PIPE_DISTANCE); // Adjust height  

  if (original->transform.position.y == 0){ // original was a top, so create a bottom   
    position.y = game->screen->transform.size.y - size.y; // Position at the bottom
  }

  return pipe_create_pipe((Transform){position, size}, PIPE_GLYPH);
}

void pipe_pair_tick(Pipe_Pair* pair, Game* game) {
    pair->top->tick(pair->top, game);
    pair->bottom->tick(pair->bottom, game);
}

void pipe_draw_pair(Pipe_Pair* pair, Game* game){
    pair->top->draw(pair->top, game);
    pair->bottom->draw(pair->bottom, game);
}

void pipe_tick(Object* pipe, Game* game) {
    pipe->transform.position.x -= 1; // Move the pipe left by 1 character
}

void pipe_delete_pair(Pipe_Pair pair) {
  if (pair.top) {
      free(pair.top);
  }
  if (pair.bottom) {
      free(pair.bottom);
  }
}