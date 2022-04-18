#include "AnimatedSprite.hpp"
#include "Ftint.hpp"

AnimatedSprite::AnimatedSprite(float animation_speed, std::vector<SDL_Texture*> texture_list)
	: animationSpeed(animation_speed), textureList(texture_list) {
	currentFrame = 0;
	texture = textureList[ftint(currentFrame)];
}

// Add to the currentframe, reset if it is too high and get the fram our of the list (vector)
SDL_Texture* AnimatedSprite::animate(double deltaTime) {
	currentFrame += animationSpeed * float(deltaTime);
	if (currentFrame > textureList.size() - 1) {
		currentFrame = 0;
	}
	texture = textureList[ftint(currentFrame)];
	return texture;
}