#include "util.h"
#include "state.h"

int WASP_KeyDown(SDL_KeyCode key);
int WASP_KeyUp(SDL_KeyCode key);
int WASP_KeyPressed(SDL_KeyCode key);
int WASP_ResetKeyStates();
int WASP_UpdateKeyState(SDL_KeyCode key, int value);
