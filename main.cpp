#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "Entity.hpp"
#include "Ftint.hpp"
#include "MovingEntity.hpp"
#include "Player.hpp"
#include "GroundTile.hpp"
#include "Camera.hpp"
#include "AnimatedSprite.hpp"
#include "QuadMech.hpp"
#include "Ground.hpp"
#include "Mechs.hpp"
#include "Text.hpp"

#define Log(x) std::cout << x << std::endl;

int main(int argc, char* args[])
{
	int winW = 1920;
	int winH = 1080;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Game game = Game("Illre", winW, winH);

	Camera camera(0.0f, 0.0f);

#pragma region
	SDL_Texture* playerIdle0 = IMG_LoadTexture(game.renderer, "assets/player/idle/Aidle0.png");
	SDL_Texture* playerIdle1 = IMG_LoadTexture(game.renderer, "assets/player/idle/Aidle1.png");
	SDL_Texture* playerIdle2 = IMG_LoadTexture(game.renderer, "assets/player/idle/Aidle2.png");
	SDL_Texture* playerIdle3 = IMG_LoadTexture(game.renderer, "assets/player/idle/Aidle3.png");
	SDL_Texture* playerIdle4 = IMG_LoadTexture(game.renderer, "assets/player/idle/Aidle4.png");
	std::vector<SDL_Texture*> playerIdleList =
	{ playerIdle0, playerIdle1, playerIdle2, playerIdle3, playerIdle4 };
	AnimatedSprite playerIdleAnim(10.0f, playerIdleList);

	SDL_Texture* playerRun0 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk0.png");
	SDL_Texture* playerRun1 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk1.png");
	SDL_Texture* playerRun2 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk2.png");
	SDL_Texture* playerRun3 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk3.png");
	SDL_Texture* playerRun4 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk4.png");
	SDL_Texture* playerRun5 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk5.png");
	SDL_Texture* playerRun6 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk6.png");
	SDL_Texture* playerRun7 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk7.png");
	SDL_Texture* playerRun8 = IMG_LoadTexture(game.renderer, "assets/player/walk/AWalk8.png");
	std::vector<SDL_Texture*> playerRunList =
	{ playerRun0, playerRun1, playerRun2, playerRun3, playerRun4, playerRun5, playerRun6, playerRun7, playerRun8 };

	SDL_Texture* playerShoot = IMG_LoadTexture(game.renderer, "assets/player/AShoot.png");

	Player player = Player(playerIdle0, 3.0f, playerIdleList, playerRunList, winW / 2, winH / 2, 16 * 4, 16 * 4, true, 1.0f, 0.2f, 200.0f, 200.0f, 150.0f);
	Player::Bullets bullets = Player::Bullets(winW, winH);
	SDL_Texture* bulletTexture = IMG_LoadTexture(game.renderer, "assets/squares/whitesquare.png");
	SDL_SetTextureColorMod(bulletTexture, 191, 38, 38);
#pragma endregion PLAYER

#pragma region
	SDL_Texture* mech0 = IMG_LoadTexture(game.renderer, "assets/quadleggedmechspider/walking/mech0.png");
	SDL_Texture* mech1 = IMG_LoadTexture(game.renderer, "assets/quadleggedmechspider/walking/mech1.png");
	SDL_Texture* mech2 = IMG_LoadTexture(game.renderer, "assets/quadleggedmechspider/walking/mech2.png");
	SDL_Texture* mech3 = IMG_LoadTexture(game.renderer, "assets/quadleggedmechspider/walking/mech3.png");
	SDL_Texture* mech4 = IMG_LoadTexture(game.renderer, "assets/quadleggedmechspider/walking/mech4.png");
	SDL_Texture* mech5 = IMG_LoadTexture(game.renderer, "assets/quadleggedmechspider/walking/mech5.png");
	std::vector<SDL_Texture*> mechWalkList = { mech0, mech1, mech2, mech3, mech4, mech5 };

	Mechs mechs = Mechs(winW, winH, mechWalkList);

	float spawnMechIncreaser = 0;

#pragma endregion QUADMECH

	SDL_Texture* stoneTexture = IMG_LoadTexture(game.renderer, "assets/squares/stonesquare.png");

	Ground ground = Ground(winW, winH, stoneTexture);
	ground.generateSpawn();

	int score = 0;
	Text scoreText("score: " + std::to_string(score), 50, { 255, 255, 255, 255 }, "assets/orange juice.ttf", 10, 10, false, game.renderer);

	Uint64 nowTime = SDL_GetPerformanceCounter();
	Uint64 lastTime = 0;
	double deltaTimeR = 0;
	double deltaTime = 0;

	bool spawnQuads = false;

	bool pause = false;

	bool mousePressed = false;
	float shootCooldown = 0;
	bool shootTrue = false;
	float shootTextureTime = 0;

	while (game.running) {
		lastTime = nowTime;
		nowTime = SDL_GetPerformanceCounter();
		deltaTime = double((nowTime - lastTime) / double(SDL_GetPerformanceFrequency()));

		game.events(pause, mousePressed);

		if (pause) {

			deltaTime -= 0.5 * deltaTime;
		}
		else{
			deltaTime += 0.1 * deltaTime;
		}
		
		game.clear(0, 0, 0);

		camera.cameraUpdate(player.x + player.w / 2 - winW / 2.0f, player.y + player.h / 2 - winH / 2.0f, deltaTime * 1.5f);

		player.inputUpdate(deltaTime);

		mechs.update(player.x + player.w / 2, player.y + player.w / 2, camera.x, camera.y, deltaTime);

		ground.update(camera.x, camera.y, deltaTime);

		shootCooldown += deltaTime;
		if (mousePressed && shootCooldown > 0.2f) {
			bullets.spawnBullet(bulletTexture, player.x + player.w / 2, player.y + 30, 3, 20, 1000.0f, camera.x, camera.y);
			shootCooldown = 0.0f;
			shootTrue = true;

			int mx, my;
			SDL_GetMouseState(&mx, &my);
			if (mx < player.sRect.x)
				player.flipped = true;
			if (mx > player.sRect.x) {
				player.flipped = false;
			}
		}
		if (shootTrue) {
			shootTextureTime += deltaTime;
			if (shootCooldown < 0.2f && player.xS == 0.0f) {
				player.texture = playerShoot;
			}
			else {
				shootTextureTime = 0;
				shootTrue = false;
			}
		}
		
		bullets.update(deltaTime);

		for (int i = 0; i < ground.tilesOnScreen.size(); ++i) {
			if (player.groundStop(ground.tilesOnScreen[i].wRect, -15, 0)) {
				player.jumps = 1;
			}

			for (int g = 0; g < mechs.mechsOnScreen.size(); ++g) {
				mechs.mechsOnScreen[g].groundStop(ground.tilesOnScreen[i].wRect, 0, 0);
			}

			for (int o = 0; o < bullets.bullets.size();) {
				if (bullets.bullets[o].collideRect(ground.tilesOnScreen[i].wRect, 0, 0)) {
					bullets.bullets.erase(bullets.bullets.begin() + o);
				}
				else {
					++o;
				}
			}

			game.render(ground.tilesOnScreen[i].texture, &ground.tilesOnScreen[i].sRect);
		}

		if (fabsf(player.xS) > 0) {
			spawnMechIncreaser += deltaTime;
			if (spawnMechIncreaser > ftint(2.0f / float(deltaTime))) {
				if (player.xS < 0) {
					if (rand() % ftint(2.0f / float(deltaTime) - spawnMechIncreaser) == 0)
						mechs.spawnMech(ground.recordLowX - 100, player.y);
				}
				if (player.xS > 0) {
					if (rand() % ftint(2.0f / float(deltaTime) - spawnMechIncreaser) == 0)
						mechs.spawnMech(ground.recordHighX + 100, player.y);
				}
			}
		}
		

		for (int i = 0; i < mechs.mechsOnScreen.size(); ++i) {
			if (mechs.mechsOnScreen[i].collideRect(player.wRect, -15, 0)) {
				if (player.xC + player.w + 14 > mechs.mechsOnScreen[i].x && player.xC - 14 < mechs.mechsOnScreen[i].x + mechs.mechsOnScreen[i].w) {
					player.yC = mechs.mechsOnScreen[i].yC - player.h;
					player.yS = 0.0f;
					//player.xS = mechs.mechsOnScreen[i].xS;
					player.jumps = 1;
				}
				else {
					if (player.xC < mechs.mechsOnScreen[i].xC) {
						player.xC = mechs.mechsOnScreen[i].x - player.w + 15;
					}
					if (player.xC > mechs.mechsOnScreen[i].xC) {
						player.xC = mechs.mechsOnScreen[i].x + mechs.mechsOnScreen[i].w - 15;
					}
				}
				
			}
			for (int o = 0; o < bullets.bullets.size();) {
				if (bullets.bullets[o].collideRect(mechs.mechsOnScreen[i].wRect, 0, 0)) {
					bullets.bullets.erase(bullets.bullets.begin() + o);
					mechs.mechsOnScreen[i].health -= 1;
					if (mechs.mechsOnScreen[i].health <= 0) {
						score += 1;
					}
				}
				else {
					++o;
				}
			}
			mechs.mechsOnScreen[i].rearUpdate(camera.x, camera.y);
			game.renderFlipped(mechs.mechsOnScreen[i].texture, &mechs.mechsOnScreen[i].sRect, mechs.mechsOnScreen[i].flipped);
		}

		for (int i = 0; i < bullets.bullets.size(); ++i) {
			bullets.bullets[i].rearUpdate(camera.x, camera.y);
			if (bullets.bullets[i].onScreen(winW, winH, 0)) {
				game.renderWithRotation(bullets.bullets[i].texture, &bullets.bullets[i].sRect, bullets.bullets[i].rotation);
			}
		}

		player.rearUpdate(camera.x, camera.y);
		
		game.renderFlipped(player.texture, &player.sRect, player.flipped);

		scoreText.text = "score: " + std::to_string(score);
		scoreText.update();
		game.render(scoreText.texture, &scoreText.rect);

		game.present();
	}

	game.quit();
	return 0;
}