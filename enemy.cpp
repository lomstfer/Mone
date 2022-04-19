#include "Enemy.hpp"
#include <stdlib.h>

Enemy::Enemy(SDL_Texture* texture, float animation_speed, std::vector<SDL_Texture*> walk_list, float position_x, float position_y, int width, int height, bool centered, float speed, float gravity)
				 : MovingEntity(texture, position_x, position_y, width, height, centered, 0.0f, 0.0f, speed),
				   gravity(gravity)
{
	direction = rand() % 2;
	if (direction == 0) {
		direction = -1;
	}

	patrolDirectionTime = 0;
	patrolDirectionRandomTime = rand() % 2 + 3;
	speedLimit = 200.0f;

	onScreenCheck = false;

	walk = AnimatedSprite(animation_speed, walk_list);

	health = 3;
}

void Enemy::patrolUpdate(double deltaTime, float player_x, float player_y, float player_width, float player_height) {
	texture = walk.animate(deltaTime);

	yS += gravity * float(deltaTime);

	patrolDirectionTime += float(deltaTime);

	if (patrolDirectionTime > patrolDirectionRandomTime) {
		direction *= -1;
		patrolDirectionTime = 0;
		patrolDirectionRandomTime = rand() % 2 + 3;
	}

	if (xS >= 0) {
		flipped = false;
	}
	if (xS < 0) {
		flipped = true;
	}

	if (direction == 1) {
		xS += speed * float(deltaTime);
	}

	if (direction == -1) {
		xS -= speed * float(deltaTime);
	}

	if (xS > speedLimit) {
		xS = speedLimit;
	}

	if (xS < -speedLimit) {
		xS = -speedLimit;
	}

	// Distance to the player calculations, pythagoras
	float pxD = (x + w / 2.0f) - (player_x + player_width);
	float pyD = (y + h / 2.0f) - (player_y + player_height);
	float pD = sqrt(pow(pxD, 2.0f) + pow(pyD, 2.0f));


	if (pD < 1000 && pD > 150) {
		if (pxD < 0) {
			if (xS < 0) {
				xS *= -1;
			}
		}

		if (pxD > 0) {
			if (xS > 0) {
				xS *= -1;
			}
		}
	}

	walk.animationSpeed = fabsf(xS * speed) / 10.0f;

	moveUpdate(deltaTime);
}