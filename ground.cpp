#include "Ground.hpp"
#include "Ftint.hpp"
#include <algorithm>

#include <iostream>
#include <string>

#define Log(x) std::cout << x << std::endl;

Ground::Ground(int window_width, int window_height, SDL_Texture* stone_texture) 
	: winW(window_width), winH(window_height), stoneTexture(stone_texture) {
	tilesOnScreenNumber = 0;
	
	spawningArea = 250;
	deep = 50;
	generateAmount = 1;
	scale = 16;
	gap = 1;

	recordHighX = winW / 2 + spawningArea / 2 * (scale + gap);
	makeMoreGroundRight = false;

	recordLowX = winW / 2 - spawningArea / 2 * (scale + gap);
	makeMoreGroundLeft = false;

	elevationTime = 0;
	randomElevationTime = 0;
	elevationRight = 0;
	elevationLeft = 0;

	lowestY = 0;
	lowyX = 0;

	flatNess = 20;
	roughNessIncreaser = 0;
}

void Ground::generateSpawn() {
	for (int i = 0; i < spawningArea / 2 + 1; ++i) {
		int surfaceDone = 0;
		for (int o = 0; o < deep; ++o) {
			/*if (surfaceDone == 0) {
				surfaceDone = 1;
				surfaceTilesOnScreen.emplace_back(stoneTexture, winW / 2 + i * (scale + gap), winH / 2 + o * (scale + gap), scale, scale);
			}
			else {*/
				tiles.emplace_back(stoneTexture, winW / 2 + i * (scale + gap), winH / 2 + o * (scale + gap), scale, scale);
				tiles.emplace_back(stoneTexture, winW / 2 - i * (scale + gap), winH / 2 + o * (scale + gap), scale, scale);
			/*}*/
		}
	}
}

void Ground::update(float camera_x, float camera_y, double deltaTime) {
	// Iteration: update and get the new record positions //
	tilesOnScreenNumber = 0;
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].update(camera_x, camera_y);

		if (tiles[i].onScreenX(winW, 0) && tiles[i].onScreen == false) {
			tiles[i].onScreen = true;
			tilesOnScreen.push_back(tiles[i]);
		}
	}

	lowestY = 0;
	lowyX = 0;

	for (int i = 0; i < tilesOnScreen.size();) {
		tilesOnScreen[i].update(camera_x, camera_y);

		if (tilesOnScreen[i].x <= recordLowX) {
			recordLowX = ftint(tilesOnScreen[i].x);
			makeMoreGroundLeft = true;
			makeMoreGroundRight = false;
		}

		if (tilesOnScreen[i].x >= recordHighX) {
			recordHighX = ftint(tilesOnScreen[i].x);
			makeMoreGroundRight = true;
			makeMoreGroundLeft = false;
		}

		if (tilesOnScreen[i].y < lowestY) {
			lowestY = tilesOnScreen[i].y;
			lowyX = tilesOnScreen[i].x;
		}

		tilesOnScreenNumber += 1;

		if (tilesOnScreen[i].onScreenX(winW, 0) == false && tilesOnScreen[i].onScreen == true) {
			tilesOnScreen[i].onScreen = false;
			tiles.push_back(tilesOnScreen[i]);
			tilesOnScreen.erase(tilesOnScreen.begin() + i);
		}
		else {
			++i;
		}
	}

	// Generate more terrain if not enough is on screen //
	if (tilesOnScreenNumber < winW / (scale + gap) * deep) {
		elevationTime += float(deltaTime);
		if (elevationTime > randomElevationTime) {
			randomElevationTime = float(rand() % 2) / 10.0f;
			elevationTime = 0;
		}

		roughNessIncreaser += (float)deltaTime / 20.0f;
		flatNess -= ftint(roughNessIncreaser);

		if (flatNess <= 3) {
			flatNess = 3;
		}

		int randomneg11 = rand() % flatNess;

		if (randomneg11 == 2) {
			randomneg11 = -1;
		}

		if (randomneg11 != 1 && randomneg11 != -1) {
			randomneg11 = 0;
		}

		int lastElevationRight = elevationRight;
		int lastElevationLeft = elevationLeft;

		for (int i = 1; i < generateAmount + 1; ++i) {
			for (int o = 0; o < deep; ++o) {
				int layerElevation = rand() % 2 + 1;

				if (makeMoreGroundRight) {
					elevationRight = lastElevationRight + randomneg11;
					tiles.emplace_back(stoneTexture, ftint(recordHighX) + i * (scale + gap), winH / 2 + o * (scale + gap) + (elevationRight * (scale + gap)), scale, scale);
				}
				if (makeMoreGroundLeft) {
					elevationLeft = lastElevationLeft + randomneg11;
					tiles.emplace_back(stoneTexture, ftint(recordLowX) - i * (scale + gap), winH / 2 + o * (scale + gap) + (elevationLeft * (scale + gap)), scale, scale);
				}
			}
		}
	}

}