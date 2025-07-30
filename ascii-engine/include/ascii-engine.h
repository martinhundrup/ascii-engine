/*
*	copyright Martin Hundrup
*/

/*
*	ascii-engine.h contains top-level includes and base 
*	structure for the engine. 
*/

#ifndef ASCII_ENGINE_H
#define ASCII_ENGINE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

// x and y integer coordinate pair
typedef struct vector2 {
  int x, y;
} Vector2;

// x and y floating point coordinate pair
typedef struct vector2_f {
  float x, y;
} Vector2_F;

// position size integer pair
typedef struct {
  Vector2 position;
  Vector2 size;
} Transform;

// position size floating point pair
typedef struct {
  Vector2_F position;
  Vector2_F size;
} Transform_F;

// returns 1 if the two vectors are equal, 0 otherwise.
int compareVectors(Vector2* a, Vector2* b);

// Checks if the inner transform is completely within the outer transform.
// Returns 1 if inner is inside outer (edges can touch), 0 otherwise.
int checkBounds(Transform inner, Transform outer);

#endif
