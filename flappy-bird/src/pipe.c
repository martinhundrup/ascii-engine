/*
*	copyright Martin Hundrup
*/

/*
*	pipe.c contains function implementations for pipe.h 
*/

#include "../include/pipe.h"

Pipe flappy_createPipe(Transform transform, Glyph glyph) {
    Pipe pipe;
    pipe.transform = transform;
    pipe.glyph = glyph;
    return pipe;
}

int flappy_drawPipe(Screen* screen, Pipe* pipe) {
    if (!screen || !pipe) return -1;
    return screen_fillRect(screen, pipe->transform.position, pipe->transform.size, pipe->glyph);
}

// pipe widths are fixed at PIPE_WIDTH characters wide
// pipe heights are random between PIPE_HEIGHT_MIN and PIPE_HEIGHT_MAX characters

Pipe flappy_createBottomPipe(Screen* screen){
  Vector2 size = {PIPE_WIDTH, getRandomRange(PIPE_HEIGHT_MIN, PIPE_HEIGHT_MAX)};
  Vector2 position = {screen->_size.x - size.x, screen->_size.y - size.y};
  return flappy_createPipe((Transform){position, size}, PIPE_GLYPH);
}

Pipe flappy_createTopPipe(Screen* screen){
  Vector2 size = {PIPE_WIDTH, getRandomRange(PIPE_HEIGHT_MIN, PIPE_HEIGHT_MAX)};
  Vector2 position = {screen->_size.x - size.x, 0};
  return flappy_createPipe((Transform){position, size}, PIPE_GLYPH);
}

Pipe_Pair flappy_createRandomPipePair(Screen* screen) {
    Pipe_Pair pair;
    pair.top = flappy_createTopPipe(screen);
    pair.bottom = flappy_createRepricolPipe(screen, &pair.top);
    return pair;
}

Pipe flappy_createRepricolPipe(Screen* screen, Pipe* original) {
  Vector2 position = {original->transform.position.x, 0}; // Start at the same x position
  Vector2 size = original->transform.size;
  size.y = screen->_size.y - (original->transform.size.y + PIPE_DISTANCE); // Adjust height  

  if (original->transform.position.y == 0){ // original was a top, so create a bottom   
    position.y = screen->_size.y - size.y; // Position at the bottom
  }

  return flappy_createPipe((Transform){position, size}, PIPE_GLYPH);
}

void flappy_movePairLeft(Pipe_Pair* pair, int distance) {
    pair->top.transform.position.x -= distance;
    pair->bottom.transform.position.x -= distance;
}