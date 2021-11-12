#ifndef WASP_H
#define WASP_H

#define WASP_VERSION = 1
#define WASP_FALSE = 0
#define WASP_TRUE 1

#include "util.h"

#include "window.h"
#include "state.h"
#include "keyboard.h"

/* Initiate wasp with callback pointers */
int WASP_Init(_WASP_CALLBACK start, _WASP_CALLBACK update, _WASP_CALLBACK destroy);

/* Render to window */
int WASP_Render();

/* WASP internal event hander */
int WASP_EventHandler();

/* Write pixel to screen */
int WASP_DrawPixel(wColor drawColor, v2i drawpoint);

/* Write line to screen */
int WASP_DrawLine(wColor drawColor, v2i p1, v2i p2);

#endif
