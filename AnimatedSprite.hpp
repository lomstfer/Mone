#pragma once
#include <SDL.h>
#include <vector>

class AnimatedSprite {
public:
	AnimatedSprite(float animation_speed, std::vector<SDL_Texture*> texture_list);
	SDL_Texture* animate(double deltaTime);

	float animationSpeed;
	float currentFrame;
	std::vector<SDL_Texture*> textureList;
	SDL_Texture* texture;

	AnimatedSprite() = default;
};