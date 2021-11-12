#include "waspsim/wasp.h"
#include <math.h>

void start();
void update();
void destroy();

v2i size;
v2i base;
v2 playerPos;
float PI = 3.141592f;
float a = 0;
float rotationSpeed;
float moveSpeed;
float simSpeed = 3.0f;

typedef struct
{
	int active;
	v2 position;
	v2 velocity;
	v2 acceleration;
	float mass;
	float aliveTimer;
} entity;

#define ENTITY_COUNT 20000
entity projectiles[ENTITY_COUNT];

int main(int argc, char* argv[])
{
	WASP_Init(&start, &update, &destroy);
	return 0;
}

void start()
{
	printf("Starting!\n");
	size = WASP_v2i(state.simulation->screenSize.x, state.simulation->screenSize.y);

	a = PI;
	rotationSpeed = 2.0f * PI;
	moveSpeed = 160.0f;
	playerPos = WASP_v2(size.x / 2.0f, size.y - 50.0f);
}

void update()
{
	double deltatime = state.simulation->deltatime;
	//double deltatime = 0.003f;
	printf("Deltatime: %f | FPS: %i\n", simulation.deltatime, simulation.fps);

	if (WASP_KeyPressed(SDLK_LEFT))
	{
		a += rotationSpeed * deltatime;
	}
	if (WASP_KeyPressed(SDLK_RIGHT))
	{
		a -= rotationSpeed * deltatime;
	}
	if (WASP_KeyPressed(SDLK_w))
	{
		playerPos.y -= moveSpeed * deltatime;
	}
	if (WASP_KeyPressed(SDLK_d))
	{
		playerPos.x += moveSpeed * deltatime;
	}
	if (WASP_KeyPressed(SDLK_s))
	{
		playerPos.y += moveSpeed * deltatime;
	}
	if (WASP_KeyPressed(SDLK_a))
	{
		playerPos.x -= moveSpeed * deltatime;
	}

	base.x = playerPos.x;
	base.y = playerPos.y;
	v2i tip = WASP_v2i(base.x + 25 * sinf(a), base.y + 25 * cosf(a));

	wColor white = WASP_wColor(255, 255, 255, 255);
	wColor particleColor = WASP_wColor(100, 100, 255, 255);
	WASP_DrawLine(white, base, tip);

	int fired = 9;
	v2i pp;
	entity projectile, lastProjectile;
	for (int i = 0; i < ENTITY_COUNT; i++)
	{
		projectile = projectiles[i];

		if (WASP_KeyPressed(SDLK_SPACE) && fired != 0)
		{
			if (projectile.active == 0)
			{
				float fireAngle = a + (fired - 5 + ((float)rand() / (float)(RAND_MAX))) * (PI / 180.0f)  * 3;
				float fireSpeedMult = 80.0f + ((float)rand() / (float)(RAND_MAX)) * 3;
				//float fireAngle = a;
				//float fireSpeedMult = speedMult;

				projectile.active = 1;
				projectile.position = WASP_v2(tip.x, tip.y);
				projectile.velocity = WASP_v2(sinf(fireAngle) * fireSpeedMult, cosf(fireAngle) * fireSpeedMult);
				projectile.acceleration.y = 9.82f * 8.0f;
				projectile.aliveTimer = 0.0f;
				projectiles[i] = projectile;
				fired--;
			}
		}

		if (projectile.active)
		{
			projectile.velocity.x += projectile.acceleration.x * deltatime * simSpeed;
			projectile.velocity.y += projectile.acceleration.y * deltatime * simSpeed;

			projectile.position.x += projectile.velocity.x * deltatime * simSpeed;
			projectile.position.y += projectile.velocity.y * deltatime * simSpeed;

			projectile.aliveTimer += deltatime;

			particleColor.r = (6.0f - projectile.aliveTimer) * 42.5f;
			particleColor.g = (6.0f - projectile.aliveTimer) * 42.5f;

			pp.x = projectile.position.x;
			pp.y = projectile.position.y;

			WASP_DrawPixel(particleColor, pp);

			if (projectile.position.y > size.y)
			{
				projectile.velocity.y = -projectile.velocity.y;
			}

			if (projectile.position.x >= size.x || projectile.position.x <= 0)
			{
				projectile.velocity.x = -projectile.velocity.x;
			}

			if (projectile.aliveTimer >= 6.0f)
			{
				projectile.active = 0;
			}
		}

		projectiles[i] = projectile;
		lastProjectile = projectile;
	}
}

void destroy()
{
	printf("Destroyed\n");
}
