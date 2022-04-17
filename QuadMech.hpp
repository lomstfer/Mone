#pragma once
#include "MovingEntity.hpp"
#include "AnimatedSprite.hpp"

class QuadMech : public MovingEntity {
public:
	QuadMech(SDL_Texture* texture, float animation_speed, std::vector<SDL_Texture*> walk_list, float position_x, float position_y, int width, int height, bool centered, float speed, float gravity);
	void patrolUpdate(double deltaTime, float player_x, float player_y);

	float gravity;
	AnimatedSprite walk;
	int direction;
	float patrolDirectionRandomTime;
	float patrolDirectionTime;
	float speedLimit;

	bool onScreen;

	int health;
};