#include "structs.h"

/* Constructor */
/* WASP - Vector 3 FLOAT */
v3 WASP_v3(float x, float y, float z)
{
	v3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}
/* Constructor */
/* WASP - Vector 2 FLOAT */
v2 WASP_v2(float x, float y)
{
	v2 vector;
	vector.x = x;
	vector.y = y;
	return vector;
}
/* Constructor */
/* WASP - Vector 3 INT */
v3i WASP_v3i(int x, int y, int z)
{
	v3i vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}
/* Constructor */
/* WASP - Vector 2 INT */
v2i WASP_v2i(int x, int y)
{
	v2i vector;
	vector.x = x;
	vector.y = y;
	return vector;
}
/* Constructor */
/* WASP - Color INT */
wColor WASP_wColor(int r, int g, int b, int a)
{
	wColor color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}
