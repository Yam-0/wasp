#ifndef WASP_STRUCTS_H
#define WASP_STRUCTS_H

/* WASP - Float vector 3 */
typedef struct
{
	float x;
	float y;
	float z;
} v3;

/* WASP - Float vector 2 */
typedef struct
{
	float x;
	float y;
} v2;

/* WASP - Int vector 3 */
typedef struct
{
	int x;
	int y;
	int z;
} v3i;

/* WASP - Int vector 2 */
typedef struct
{
	int x;
	int y;
} v2i;

/* WASP - Color (R, G, B, A) */
typedef struct
{
	int r;
	int g;
	int b;
	int a;
} wColor;

/* Constructor references */
v3 WASP_v3(float x, float y, float z);
v2 WASP_v2(float x, float y);
v3i WASP_v3i(int x, int y, int z);
v2i WASP_v2i(int x, int y);
wColor WASP_wColor(int r, int g, int b, int a);

#endif
