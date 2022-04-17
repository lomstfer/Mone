#include "ScreenObject.h"

ScreenObject::ScreenObject(SDL_Texture* texture, int position_x, int position_y, int width, int height, bool centered)
			: texture(texture) {
	rect = { position_x,position_y, width, height };
	if (centered) {
		rect.x -= rect.w / 2;
		rect.y -= rect.h / 2;
	}
}

bool ScreenObject::collidePoint(int x, int y){
	if (x > rect.x && x < rect.x + rect.w &&
		y > rect.y && y < rect.y + rect.h) {
		return true;
	}
	return false;
}