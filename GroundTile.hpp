#pragma once
#include <SDL.h>
#include "MovingEntity.hpp"
#include <vector>

class GroundTile : public Entity {
public:
	GroundTile(SDL_Texture* texture, int position_x, int position_y, int width, int height);

	bool onScreen;
};