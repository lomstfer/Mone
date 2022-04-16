#include <SDL.h>

class Collider {
	float x;
	float y;
	float w;
	float h;

	Collider(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {

	}

	bool collideRect(SDL_Rect rect2, int gap) {
		if (x + w > rect2.x - gap &&
			x < rect2.x + rect2.w + gap &&
			y + h > rect2.y - gap &&
			y < rect2.y + rect2.h + gap) {
			return true;
		}
		return false;
	}

	bool collideCircle(SDL_Rect rect2, int gap) {
		float distanceX = fabsf((x + w / 2.0f) - (float(rect2.x) + float(rect2.w) / 2.0f));
		float distanceY = fabsf((y + h / 2.0f) - (float(rect2.y) + float(rect2.h) / 2.0f));
		float distance = float(sqrt(pow(distanceX, 2) + pow(distanceY, 2)));

		if (distance < float(w / 2.0f + float(rect2.w) / 2.0f)) {
			return true;
		}
		return false;
	}
};