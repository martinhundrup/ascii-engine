/*
*	copyright Martin Hundrup
*/

/*
*	ascii-engine.c contains function implementations for ascii-engine.h 
*/

#include "../include/ascii-engine.h"

int compareVectors(Vector2* a, Vector2* b) {
  return (a->x == b->x && a->y == b->y);
}

int checkBounds(Transform inner, Transform outer){
	return (
		inner.position.x >= outer.position.x && 
		inner.position.x + inner.size.x <= outer.position.x + outer.size.x && 
		inner.position.y >= outer.position.y && 
		inner.position.y + inner.size.y <= outer.position.y + outer.size.y
	);
}