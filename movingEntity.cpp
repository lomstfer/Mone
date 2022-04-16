#include "MovingEntity.hpp"
#include <math.h>

MovingEntity::MovingEntity(SDL_Texture* texture, float position_x, float position_y, int width, int height, bool centered, float x_speed, float y_speed, float speed)
						 : Entity(texture, position_x, position_y, width, height, centered), 
					       xS(x_speed), yS(y_speed), speed(speed) {
	xC = x;
	yC = y;
	flipped = false;
}

void MovingEntity::moveUpdate(double deltaTime) {
	xC += xS * speed * (float)deltaTime;
	yC += yS * speed * (float)deltaTime;
}

void MovingEntity::rearUpdate(float camera_x, float camera_y) {
	x = xC;
	y = yC;

	update(camera_x, camera_y);
}

bool MovingEntity::groundStop(XYWH rect2, int x_gap, int y_gap) {
	if (xC + w > rect2.x - x_gap &&
		xC < rect2.x + rect2.w + x_gap &&
		yC + w > rect2.y + y_gap &&
		yC < rect2.y + rect2.h - y_gap) {

		yC = rect2.y - h + y_gap;
		yS = 0.0f;

		return true;
	}
	return false;
}

bool MovingEntity::collideRect(XYWH rect2, int x_gap, int y_gap) {
	if (xC + w > rect2.x - x_gap &&
		xC < rect2.x + rect2.w + x_gap &&
		yC + w > rect2.y + y_gap &&
		yC < rect2.y + rect2.h - y_gap) {
		return true;
	}
	return false;
}

bool MovingEntity::collideCircle(XYWH rect2, int x_gap, int y_gap) {
	float distanceX = fabsf((xC + w / 2.0f) - (float(rect2.x) + float(rect2.w) / 2.0f));
	float distanceY = fabsf((yC + h / 2.0f) - (float(rect2.y) + float(rect2.h) / 2.0f));
	float distance = float(sqrt(pow(distanceX, 2) + pow(distanceY, 2)));

	if (distance < float(w / 2.0f + float(rect2.w / 2))) {
		return true;
	}
	return false;
}