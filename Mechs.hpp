#include <SDL.h>
#include "QuadMech.hpp"
#include <vector>

class Mechs {
public:
	Mechs(int window_width, int window_height, std::vector<SDL_Texture*> walk_list);

	std::vector<QuadMech> mechs;
	std::vector<QuadMech> mechsOnScreen;

	std::vector<SDL_Texture*> walkList;

	int winW;
	int winH;

	void update(float camera_x, float camera_y, double deltaTime);
	void spawnMech(float position_x, float position_y);
};