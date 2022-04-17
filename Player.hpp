#pragma once
#include "MovingEntity.hpp"
#include "AnimatedSprite.hpp"

class Player : public MovingEntity {
public:
	Player(SDL_Texture* texture, float animation_speed, std::vector<SDL_Texture*> idle_list, std::vector<SDL_Texture*> run_list, float position_x, float position_y, int width, int height, bool centered, float speed, float damp, float walk_force, float jump_force, float gravity);

	void inputUpdate(double deltaTime);

	bool flipped;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	float jumpForce;
	int jumps;
	float gravity;
	float walkForce;
	float damp;
	float speedLimit;

	AnimatedSprite idle;
	AnimatedSprite running;

	class Bullet : public MovingEntity {
	public:
		Bullet(SDL_Texture* texture, float position_x, float position_y, float width, float height, float x_speed, float y_speed, float speed, float rotation);
		float rotation;
	};

	class Bullets {
	public:
		Bullets(int window_width, int window_height);
		void update(float camera_x, float camera_y, double deltaTime);

		std::vector<Bullet> bullets;

		int winW;
		int winH;

		void spawnBullet(SDL_Texture* texture, float position_x, float position_y, float width, float height, float speed, float camera_x, float camera_y);
	};


};