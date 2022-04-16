#include "Mechs.hpp"
#include <stdlib.h>

Mechs::Mechs(int window_width, int window_height, std::vector<SDL_Texture*> walk_list)
	       : winW(window_width), winH(window_height), walkList(walk_list) {
}

void Mechs::update(float camera_x, float camera_y, double deltaTime) {
	// Iteration: update and get the new record //
	for (int i = 0; i < mechs.size();) {
		mechs[i].update(camera_x, camera_y);

		if (mechs[i].onScreenX(winW, 100) && mechs[i].onScreen == false) {
			mechs[i].onScreen = true;
			mechsOnScreen.push_back(mechs[i]);
			mechs.erase(mechs.begin() + i);
		}
		else {
			++i;
		}

	}

	for (int i = 0; i < mechsOnScreen.size();) {
		mechsOnScreen[i].patrolUpdate(deltaTime);

		if (mechsOnScreen[i].onScreenX(winW, 100) == false && mechsOnScreen[i].onScreen == true) {
			mechsOnScreen[i].onScreen = false;
			mechs.push_back(mechsOnScreen[i]);
			mechsOnScreen.erase(mechsOnScreen.begin() + i);
		}
		else if (mechsOnScreen[i].health <= 0) {
			mechsOnScreen.erase(mechsOnScreen.begin() + i);
		}
		else {
			++i;
		}
	}
}

void Mechs::spawnMech(float position_x, float position_y) {
	mechs.emplace_back(walkList[0], 10.0f, walkList, position_x, position_y, 44, 40, true, 8.0f, 150.0f);
}