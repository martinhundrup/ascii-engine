/*
*	copyright martin hundrup
*/

/*
* gameobject.h contains behavior relating to game objects.
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ascii-engine.h"
#include "../include/game.h"

typedef struct object {
    Transform transform;
    Glyph glyph; // the visual representation of the game object

    void (*init)(struct object* self, Game* game); // Initialize the game object
    void (*tick)(struct object* self, Game* game); // Update the game object state
    void (*draw)(struct object* self, Game* game); // Draw the object

} Object;

// creates a new dynamic game object instance.
Object* object_create_game_object(Transform transform, Glyph glyph);

// uninitializes the game object.
void object_init(Object* obj, Game* game);

// ticks a game object, updating its state.
void object_tick(Object* obj, Game* game);

// draws the game object to the screen.
void object_draw(Object* obj, Game* game);

#endif // GAMEOBJECT_H