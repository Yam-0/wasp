#include "util.h"

int index2D(int x, int y, int width)
{
	return (y * width + x);
}

v2i inverse_index2D(int i, int width)
{
	return WASP_v2i(i % width, i / width);
}

float overflowf(float value, float bottom, float top)
{
	float number = value;

	while (number < bottom)
	{
		number += top;
	}
	while (number > top)
	{
		number -= top;
	}

	return number;
}

float mapf(float value, float x1, float y1, float x2, float y2)
{
	return x2 + (y2 - x2) * ((value - x1) / (y1 - x1));
}

float clampf(float value, float min, float max)
{
	value = (value > max) ? max : value;
	value = (value < min) ? min : value;

	return value;
}

float relative_clampf(float value, float minus, float plus)
{
	value = (value > value + plus) ? value + plus : value;
	value = (value < value - minus) ? value - minus : value;

	return value;
}
