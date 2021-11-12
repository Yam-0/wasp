#ifndef WASP_STATE_H
#define WASP_STATE_H

#include "window.h"

typedef struct
{
	WASP_simulation *simulation;

	int running;
	int mouse_focused, keyboard_focused;
} WASP_state;

WASP_state state;

#endif
