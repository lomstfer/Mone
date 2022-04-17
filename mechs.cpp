#include "Mechs.hpp"
#include <stdlib.h>

Mechs::Mechs(int window_width, int window_height, std::vector<SDL_Texture*> walk_list)
	       : winW(window_width), winH(window_height), walkList(walk_list) {
}

void Mechs::update(float player_x, float player_y, float player_width, float player_height, float camera_x, float camera_y, double deltaTime) {
	// Iteration: update and get the new record //
	for (int i = 0; i < mechs.size();) {
		mechs[i].update(camera_x, camera_y);

		if (mechs[i].onScreen(winW, winH, 100) && mechs[i].onScreenCheck == false) {
			mechs[i].onScreenCheck = true;
			mechsOnScreen.push_back(mechs[i]);
			mechs.erase(mechs.begin() + i);
		}
		else {
			++i;
		}

	}

	for (int i = 0; i < mechsOnScreen.size();) {
		mechsOnScreen[i].patrolUpdate(deltaTime, player_x, player_y, player_width, player_height);

		if (mechsOnScreen[i].onScreen(winW, winH, 100) == false && mechsOnScreen[i].onScreenCheck == true) {
			mechsOnScreen[i].onScreenCheck = false;
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
	int size = rand() % 3;
	if (size == 0) {
		size = 3;
	}
	mechs.emplace_back(walkList[0], 10.0f, walkList, position_x, position_y, size * 32, size * 32, true, 8.0f, 150.0f);
}