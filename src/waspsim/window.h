#ifndef WASP_WINDOW_H
#define WASP_WINDOW_H

#include "util.h"
#include "structs.h"

// Callback functions
typedef void (*_WASP_CALLBACK)();

typedef struct
{
	int down, up, held;
} WASP_Key;

typedef struct
{
	v2i position, delta;
} WASP_Mouse;

typedef struct
{
	WASP_Key keys[322];
} WASP_Keyboard;

typedef struct
{
	// Core
	SDL_Window *window_handle;
	SDL_Renderer *renderer_handle;
	SDL_Surface *surface_handle;
	v2i screenSize;
	_WASP_CALLBACK start, update, destroy;

	// Input
	WASP_Mouse mouse;
	WASP_Keyboard keyboard;

	// Timing
	double deltatime;
	int fps;
} WASP_simulation;

WASP_simulation simulation;

int WASP_CreateWindow(_WASP_CALLBACK start, _WASP_CALLBACK update, _WASP_CALLBACK destroy);

#endif
