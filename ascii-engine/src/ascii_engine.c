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

int inside(Transform inner, Transform outer){
	return (
		inner.position.x >= outer.position.x && 
		inner.position.x + inner.size.x <= outer.position.x + outer.size.x && 
		inner.position.y >= outer.position.y && 
		inner.position.y + inner.size.y <= outer.position.y + outer.size.y
	);
}

int overlaps(Transform a, Transform b){
	return (
		a.position.x < b.position.x + b.size.x &&
		a.position.x + a.size.x > b.position.x &&
		a.position.y < b.position.y + b.size.y &&
		a.position.y + a.size.y > b.position.y
	);
}

int getRandomRange(int min, int max) {
  if (min > max) {
    int temp = min;
    min = max;
    max = temp;
  }
  return (rand() % (max - min + 1)) + min;
}

Vector2_F normalize(Vector2_F v, int magnitude) {
  float length = sqrt(v.x * v.x + v.y * v.y);
    if (length == 0.0f) {
        return (Vector2_F){0.0f, 0.0f}; // avoid division by zero
    }
    float scale = magnitude / length;
    return (Vector2_F){v.x * scale, v.y * scale};
}