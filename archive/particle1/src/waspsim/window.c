#include "window.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int WASP_CreateWindow(_WASP_CALLBACK start, _WASP_CALLBACK update, _WASP_CALLBACK destroy)
{
	simulation.start = start;
	simulation.update = update;
	simulation.destroy = destroy;

	simulation.screenSize.x = SCREEN_WIDTH;
	simulation.screenSize.y = SCREEN_HEIGHT;

	// Initiate SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	simulation.window_handle = SDL_CreateWindow("THE WASP ENGINE",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (simulation.window_handle == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	simulation.renderer_handle = SDL_CreateRenderer(simulation.window_handle, -1, SDL_RENDERER_ACCELERATED);
	if (simulation.renderer_handle == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	simulation.surface_handle = SDL_GetWindowSurface(simulation.window_handle);

	return 0;
}
