#pragma once
#include <SDL.h>
#include "XYWH.h"
class Entity {
public:
	Entity(SDL_Texture* texture, float position_x, float position_y, int width, int height, bool centered);
	
	void update(float camera_x, float camera_y);
	bool onScreenX(int winW, int gap);
	bool onScreen(int winW, int winH, int gap);

	SDL_Texture* texture;

	float x;
	float y;
	float w;
	float h;

	// screen rect
	SDL_Rect sRect;

	// world position rect
	XYWH wRect = XYWH(x, y, w, h);

	bool centered;
};