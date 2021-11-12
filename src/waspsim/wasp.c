#include "wasp.h"
#include <time.h>

int WASP_Init(_WASP_CALLBACK start, _WASP_CALLBACK update, _WASP_CALLBACK destroy)
{
	printf("\n---------------- USING THE WASP ENGINE ----------------\n");

	WASP_CreateWindow(start, update, destroy);
	state.simulation = &simulation;
	state.running = 1;

	// Timing
	Uint64 before = 0;
	float fpsFrequency = 1.0f;
	float fpsCooldown = 1.0f / fpsFrequency;
	double deltatime;
	double deltatimeSum = 0.0;
	int deltatimeCount = 0;

	// Start callback
	simulation.start();

	// Update loop
	while (state.running)
	{
		before = SDL_GetPerformanceCounter();

		WASP_EventHandler();

		SDL_SetRenderDrawColor(simulation.renderer_handle, 0, 0, 0, 255);
		SDL_RenderClear(simulation.renderer_handle);

		// Update callback
		simulation.update();

		WASP_Render();

		// Deltatime
		deltatime = ((SDL_GetPerformanceCounter() - before) / (double)SDL_GetPerformanceFrequency());
		simulation.deltatime = deltatime;
		deltatimeSum += deltatime;
		deltatimeCount++;

		// Fps
		fpsCooldown = (fpsCooldown >= 0) ? fpsCooldown - deltatime : 0.0f;
		if (fpsCooldown <= 0)
		{
			simulation.fps = 1.0f / (deltatimeSum / deltatimeCount);
			deltatimeSum = 0.0;
			deltatimeCount = 0;
			fpsCooldown = 1.0f / fpsFrequency;
		}
	}

	// Destroy callback
	simulation.destroy();

	SDL_DestroyRenderer(simulation.renderer_handle);
	SDL_DestroyWindow(simulation.window_handle);
	SDL_Quit();

	return 0;
}

int WASP_Render()
{
	SDL_RenderPresent(simulation.renderer_handle);
	return 0;
}

int WASP_EventHandler()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	WASP_ResetKeyStates();

	state.keyboard_focused = (state.simulation->window_handle == SDL_GetKeyboardFocus());
	state.mouse_focused = (state.simulation->window_handle == SDL_GetMouseFocus());

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	//state.simulation->screenSize.x = DM.w;
	//state.simulation->screenSize.y = DM.h;

	switch (event.type)
	{
		case SDL_QUIT:
			state.running = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;

		case SDL_MOUSEMOTION:
			break;

		case SDL_KEYDOWN:
			if (event.key.repeat == 0)
				WASP_UpdateKeyState(event.key.keysym.sym, 1);
			break;

		case SDL_KEYUP:
			WASP_UpdateKeyState(event.key.keysym.sym, 0);
			break;

		default:
			break;
	}
	return 0;
}

int WASP_DrawPixel(wColor drawColor, v2i p)
{
	SDL_SetRenderDrawColor(simulation.renderer_handle, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
	SDL_RenderDrawPoint(simulation.renderer_handle, p.x, p.y);

	return 0;
}

int WASP_DrawLine(wColor drawColor, v2i p1, v2i p2)
{
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;

	float l_tr = (float)dy / (float)dx;
	float l_angle = atanf(l_tr);
	float l_length = sqrtf(dx * dx + dy * dy);

	float xOffset;
	float yOffset;

	int l_dirM = 2 * (p2.x >= p1.x) - 1;
	xOffset = cosf(l_angle) * l_dirM;
	yOffset = sinf(l_angle) * l_dirM;

	v2i drawpoint;
	for (int i = 0; i < l_length; i++)
	{
		drawpoint.x = round(p1.x + xOffset * i);
		drawpoint.y = round(p1.y + yOffset * i);
		WASP_DrawPixel(drawColor, drawpoint);
	}

	return 0;
}

