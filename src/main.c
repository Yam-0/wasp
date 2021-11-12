#include "waspsim/wasp.h"
#include "particles.h"

void start();
void update();
void destroy();

v2i size;
v2i base;
v2 playerPos;
int drawParticle = 1;
float PI = 3.141592f;
float a = 0;
float rotationSpeed;
float moveSpeed;

float simSpeed = 3.0f;

float particleUpdatesPerSecond = 24.0f;
float particleUpdateCooldown;

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
	printf("Deltatime: %f | FPS: %i\n", simulation.deltatime, simulation.fps);

	if (WASP_KeyPressed(SDLK_LEFT))
		a += rotationSpeed * deltatime;

	if (WASP_KeyPressed(SDLK_RIGHT))
		a -= rotationSpeed * deltatime;

	if (WASP_KeyPressed(SDLK_w))
		playerPos.y -= moveSpeed * deltatime;

	if (WASP_KeyPressed(SDLK_d))
		playerPos.x += moveSpeed * deltatime;

	if (WASP_KeyPressed(SDLK_s))
		playerPos.y += moveSpeed * deltatime;

	if (WASP_KeyPressed(SDLK_a))
		playerPos.x -= moveSpeed * deltatime;

	if (WASP_KeyDown(SDLK_1))
		drawParticle = 1;

	if (WASP_KeyDown(SDLK_2))
		drawParticle = 2;

	wColor white = WASP_wColor(255, 255, 255, 255);
	v2i tip = WASP_v2i(playerPos.x + 25 * sinf(a), playerPos.y + 25 * cosf(a));
	WASP_DrawLine(white, WASP_v2i(playerPos.x, playerPos.y), tip);

	if (WASP_KeyPressed(SDLK_SPACE))
	{
		v2i point = WASP_v2i(tip.x / 4, tip.y / 4);
		add_particle(point, drawParticle);
	}

	int updateParticles = 0;
	if (particleUpdateCooldown == 0)
	{
		updateParticles = 1;
		particleUpdateCooldown = 1.0f / particleUpdatesPerSecond;
	}

	update_particles(updateParticles);
	particleUpdateCooldown = particleUpdateCooldown >= 0 ? particleUpdateCooldown - deltatime : 0.0f;

	draw_particles();
}

void destroy()
{
	printf("Destroyed\n");
}
