#include "Player.hpp"
#include "Ftint.hpp"
#include <iostream>
#include <string>

Player::Player(SDL_Texture* texture, float animation_speed, std::vector<SDL_Texture*> idle_list, std::vector<SDL_Texture*> run_list, float position_x, float position_y, int width, int height, bool centered, float speed, float damp, float walk_force, float jump_force, float gravity)
	         : MovingEntity(texture, position_x, position_y, width, height, centered, 0.0f, 0.0f, speed),
			   walkForce(walk_force), jumpForce(jump_force), damp(damp), gravity(gravity) {
	flipped = false;
	jumps = 1;

	idle = AnimatedSprite(animation_speed, idle_list);
	running = AnimatedSprite(animation_speed, run_list);

	speedLimit = 200.0f;
}

void Player::inputUpdate(double deltaTime) {
	if (keys[SDL_SCANCODE_W] && jumps > 0) {
		yS = -float(jumpForce);
		jumps -= 1;
		if (jumps < 0) {
			jumps = 0;
		}
	}

	else if (keys[SDL_SCANCODE_S]) {
		yS = float(jumpForce);
	}

	if (keys[SDL_SCANCODE_A]) {
		xS += -float(walkForce) * float(deltaTime);
		flipped = true;
	}

	else if (keys[SDL_SCANCODE_D]) {
		xS += float(walkForce) * float(deltaTime);
		flipped = false;
	}
	else {
		xS *= pow(damp, deltaTime);
	}

	if (fabsf(xS) > speedLimit) {
		if (xS < 0) {
			xS = -speedLimit;
		}
		if (xS > 0) {
			xS = speedLimit;
		}
	}

	if (fabsf(xS) < 5.0f) {
		xS = 0.0f;
	}
	if (fabsf(yS) < 1.0f && jumps > 0) {
		yS = 0.0f;
	}

	yS += gravity * float(deltaTime);

	if (jumps == 0) {
		running.animationSpeed = fabsf(xS) / 100.0f;
		idle.animationSpeed = 3.0f;
		speedLimit = 400.0f;
	}
	else {
		running.animationSpeed = fabsf(xS) / 30.0f;
		idle.animationSpeed = 3.0f;
		speedLimit = 200.0f;
	}

	if (xS != 0) {
		texture = running.animate(deltaTime);
	}
	else {
		texture = idle.animate(deltaTime);
	}

	moveUpdate(deltaTime);
}

Player::Bullet::Bullet(SDL_Texture* texture, float position_x, float position_y, float width, float height, float x_speed, float y_speed, float speed, float rotation)
: MovingEntity(texture, position_x, position_y, width, height, true, x_speed, y_speed, speed), rotation(rotation) {
}

Player::Bullets::Bullets(int window_width, int window_height) 
	: winW(window_width), winH(window_height) {

}

void Player::Bullets::update(double deltaTime) {
	for (int i = 0; i < bullets.size(); ++i) {
		bullets[i].yS += float(deltaTime) / 30.0f;
		bullets[i].rotation = atan2(bullets[i].xS, -bullets[i].yS) * 180 / M_PI;

		bullets[i].moveUpdate(deltaTime);
	}
}

void Player::Bullets::spawnBullet(SDL_Texture* texture, float position_x, float position_y, float width, float height, float speed, float camera_x, float camera_y) {
	float xS;
	float yS;

	int mX;
	int mY;

	SDL_GetMouseState(&mX, &mY);

	float dX = float(mX) + camera_x - position_x;
	float dY = float(mY) + camera_y - position_y;

	float hyp = sqrt(pow(dX, 2) + pow(dY, 2));

	dX = dX / hyp;
	dY = dY / hyp;

	xS = dX;
	yS = dY;

	float rotation = atan2(dX, -dY) * 180 / M_PI;

	bullets.emplace_back(texture, position_x, position_y, width, height, xS, yS, speed, rotation);
}