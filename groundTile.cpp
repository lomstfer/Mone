#include "GroundTile.hpp"

GroundTile::GroundTile(SDL_Texture* texture, int position_x, int position_y, int width, int height)
					 : Entity(texture, float(position_x), float(position_y), width, height, false)
{
	onScreen = false;
}