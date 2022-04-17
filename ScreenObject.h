#pragma once
#include <SDL.h>

class ScreenObject {
public:
	ScreenObject(SDL_Texture* texture, int position_x, int position_y, int width, int height, bool centered);

	SDL_Rect rect;
	SDL_Texture* texture;
};