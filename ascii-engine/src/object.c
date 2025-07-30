/*
*	copyright martin hundrup
*/

/*
*	gameobject.c contains the function impelementations for game objects.
*/

#include "../include/object.h"

Object* object_create_game_object(Transform transform, Glyph glyph) {
    Object* obj = malloc(sizeof(Object));
    if (!obj) return NULL;

    obj->transform = transform;
    obj->glyph = glyph;

    obj->tick = object_tick;
    obj->init = object_init;
    obj->draw = object_draw;

    return obj;
}

void object_init(Object* obj, Game* game) {
    return; // No default initialization logic, can be overridden by specific objects
}

void object_tick(Object* obj, Game* game) {
  return; // No default tick logic, can be overridden by specific objects
}

void object_draw(Object* obj, Game* game) {
    if (!obj || !game || !game->screen) return; // Ensure valid parameters

    // Draw the object on the screen at its transform position
    screen_fillRect(game->screen, obj->transform, obj->glyph);
}