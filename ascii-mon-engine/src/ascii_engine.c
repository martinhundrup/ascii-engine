/*
*	copyright Martin Hundrup
*/

/*
*	ascii-engine.c contains function implementations for ascii-engine.h 
*/

#include "../include/ascii-engine.h"

int compareVectors(Vector2_Int* a, Vector2_Int* b) {
  return (a->x == b->x && a->y == b->y);
}