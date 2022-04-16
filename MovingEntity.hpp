#pragma once
#include "Entity.hpp"
#include "XYWH.h"
class MovingEntity : public Entity {
public:
	MovingEntity(SDL_Texture* texture, float position_x, float position_y, int width, int height, bool centered, float x_speed, float y_speed, float speed);
	void moveUpdate(double deltaTime);
	void rearUpdate(float camera_x, float camera_y);

	bool groundStop(XYWH rect2, int x_gap, int y_gap);
	bool collideRect(XYWH rect2, int x_gap, int y_gap);
	bool collideCircle(XYWH rect2, int x_gap, int y_gap);

	// positions to check collisions and move the object with
	float xC;
	float yC;

	// speed variables
	float xS;
	float yS;

	float speed;
	bool flipped;
};