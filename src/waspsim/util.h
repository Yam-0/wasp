#ifndef WASP_UTIL_H
#define WASP_UTIL_H

// Standard libraries
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Libraries
#define SDL_MAIN_HANDLED
#include "../../include/SDL2/SDL.h"

// Wasp Core
#include "structs.h"

// Utility functions
int index2D(int x, int y, int width);
v2i inverse_index2D(int i, int width);
float overflowf(float value, float bottom, float top);
float mapf(float value, float x1, float y1, float x2, float y2);
float clampf(float value, float min, float max);
float relative_clampf(float value, float minus, float plus);

#endif
