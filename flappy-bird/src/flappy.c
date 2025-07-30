/*
*	copyright Martin Hundrup
*/

/*
*	flappy.c contains function implementations for flappy.h 
*/

#include "../include/flappy.h"

int flappy_getRandomRange(int min, int max) {
  if (min > max) {
    int temp = min;
    min = max;
    max = temp;
  }
  return (rand() % (max - min + 1)) + min;
}