#include "keyboard.h"

int WASP_KeyDown(SDL_KeyCode key)
{
	return (state.simulation->keyboard.keys[key].down);
}

int WASP_KeyUp(SDL_KeyCode key)
{
	return (state.simulation->keyboard.keys[key].up);
}

int WASP_KeyPressed(SDL_KeyCode key)
{
	return (state.simulation->keyboard.keys[key].held);
}

int WASP_ResetKeyStates()
{
	// Loop over keys
	for (int i = 0; i < 322; i++) {
		state.simulation->keyboard.keys[i].down = 0;
		state.simulation->keyboard.keys[i].up = 0;
	}

	return 0;
}

int WASP_UpdateKeyState(SDL_KeyCode key, int value)
{
	if (value)
	{
		// Key pressed
		state.simulation->keyboard.keys[key].down = 1;
		state.simulation->keyboard.keys[key].held = 1;
	}
	else
	{
		// Key released
		state.simulation->keyboard.keys[key].up = 1;
		state.simulation->keyboard.keys[key].held = 0;
	}

	return 0;
}
