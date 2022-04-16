#include "Entity.hpp"
#include "Ftint.hpp"
#include <math.h>

Entity::Entity(SDL_Texture* texture, float position_x, float position_y, int width, int height, bool centered) : texture(texture), centered(centered) {
	x = position_x;
	y = position_y;
	w = float(width);
	h = float(height);

	if (centered) {
		x -= w / 2.0f;
		y -= h / 2.0f;
	}

	wRect = XYWH(x, y, w, h);

	/*sRect.x = ftint(x);
	sRect.y = ftint(y);
	sRect.w = ftint(w);
	sRect.h = ftint(h);*/
}

void Entity::update(float camera_x, float camera_y) {
	wRect.x = x;
	wRect.y = y;
	wRect.w = w;
	wRect.h = h;

	sRect.x = ftint(x - camera_x);
	sRect.y = ftint(y - camera_y);
	sRect.w = ftint(w);
	sRect.h = ftint(h);
}

bool Entity::onScreenX(int winW, int gap) {
	if (sRect.x + sRect.w > 0 - gap && sRect.x < winW + gap) {
		return true;
	}
	return false;
}

bool Entity::onScreen(int winW, int winH, int gap) {
	if (sRect.x + sRect.w > 0 - gap && sRect.x < winW + gap &&
		sRect.y + sRect.h > 0 - gap && sRect.y < winH + gap) {
		return true;
	}
	return false;
}
