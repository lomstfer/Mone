#include "Enemies.hpp"
#include <stdlib.h>

Enemies::Enemies(int window_width, int window_height, std::vector<SDL_Texture*> walk_list)
	       : winW(window_width), winH(window_height), walkList(walk_list) {
}

void Enemies::update(float player_x, float player_y, float player_width, float player_height, float camera_x, float camera_y, double deltaTime) {
	// Iteration: update and get the new record //
	for (int i = 0; i < enemies.size();) {
		enemies[i].update(camera_x, camera_y);

		if (enemies[i].onScreen(winW, winH, 100) && enemies[i].onScreenCheck == false) {
			enemies[i].onScreenCheck = true;
			enemiesOnScreen.push_back(enemies[i]);
			enemies.erase(enemies.begin() + i);
		}
		else {
			++i;
		}

	}

	for (int i = 0; i < enemiesOnScreen.size();) {
		enemiesOnScreen[i].patrolUpdate(deltaTime, player_x, player_y, player_width, player_height);

		if (enemiesOnScreen[i].onScreen(winW, winH, 100) == false && enemiesOnScreen[i].onScreenCheck == true) {
			enemiesOnScreen[i].onScreenCheck = false;
			enemies.push_back(enemiesOnScreen[i]);
			enemiesOnScreen.erase(enemiesOnScreen.begin() + i);
		}
		else if (enemiesOnScreen[i].health <= 0) {
			enemiesOnScreen.erase(enemiesOnScreen.begin() + i);
		}
		else {
			++i;
		}
	}

}

void Enemies::spawnEnemy(float position_x, float position_y) {
	int size = rand() % 3;
	if (size == 0) {
		size = 3;
	}
	enemies.emplace_back(walkList[0], 10.0f, walkList, position_x, position_y, size * 32, size * 32, true, 8.0f, 150.0f);
}