/*
*	copyright martin hundrup
*/

/*
* gameobject.h contains behavior relating to game objects.
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ascii-engine.h"
#include "../include/draw.h"

typedef struct {
  Vector2_Int position;
  Vector2_Int size;
} Transform;

typedef struct {
    Transform transform;
    Glyph glyph; // the visual representation of the game object

    void (*tick)(struct GameObject* self, Screen* screen); // Update the game object state
    void (*init)(struct GameObject* self); // Initialize the game object
    void (*draw)(struct GameObject* self, Screen* screen); // Draw the game

} GameObject;

GameObject* create_game_object(Transform transform, Glyph glyph);
void destroy_game_object(GameObject* obj);
void update_game_object(GameObject* obj);
void draw_game_object(GameObject* obj, Screen* screen);

#endif // GAMEOBJECT_H