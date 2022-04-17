#pragma once
#include <vector>
#include "GroundTile.hpp"
#include <SDL.h>

class Ground {
public:
	Ground(int window_width, int window_height, SDL_Texture* stone_texture);

	void generateSpawn();

	void update(float camera_x, float camera_y, double deltaTime);

	int winW;
	int winH;

	std::vector<GroundTile> tiles;
	std::vector<GroundTile> tilesOnScreen;
	std::vector<GroundTile> surfaceTilesOnScreen;
	int tilesOnScreenNumber;

	int spawningArea;
	int deep;
	int scale;
	int gap;
	int generateAmount;

	int recordHighX;
	bool makeMoreGroundRight;

	int recordLowX;
	bool makeMoreGroundLeft;

	float elevationTime;
	float randomElevationTime;
	int elevationRight;
	int elevationLeft;

	int flatNess;
	float roughNessIncreaser;

	SDL_Texture* stoneTexture;
};