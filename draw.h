#ifndef DRAW_H
#define DRAW_H

#include "model.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE 0x812F
#endif

/**
* Draw the model.
*/
void draw_model(const struct Model *model);

/**
* Draw the triangles of the model.
*/
void draw_triangles(const struct Model *model);

/**
* Draw the quads of the model.
*/
void draw_quads(const struct Model *model);

/**
* Draws the ground
*/
void draw_ground(int ground);

/*
* Draws the left side of the room
*/
void draw_room_left(Room room);

/*
* Draws the right side of the room
*/
void draw_room_right(Room room);

/*
* Draws the front side of the room
*/
void draw_room_front(Room room);

/*
* Draws the back side of the room
*/
void draw_room_back(Room room);

/*
* Draws the top of the room
*/
void draw_room_top(Room room);

/*
* Draws the top of the room
*/
void draw_room_bottom(Room room);

/*
* Calls the draw_room_* and draw_ground methodes, makes the display lists
*/
void draw_environment(World world);

void draw_teapot_for_light();

/**
* Calls 
*/
void draw_entities(World world);
#endif // DRAW_H
