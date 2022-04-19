#include <SDL.h>
#include "Enemy.hpp"
#include <vector>

class Enemies {
public:
	Enemies(int window_width, int window_height, std::vector<SDL_Texture*> walk_list);

	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesOnScreen;

	std::vector<SDL_Texture*> walkList;

	int winW;
	int winH;

	void update(float player_x, float player_y, float player_width, float player_height, float camera_x, float camera_y, double deltaTime);
	void spawnEnemy(float position_x, float position_y);
};