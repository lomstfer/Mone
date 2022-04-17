#include "Game.hpp"
#include <iostream>
#include "SDL_ttf.h"

Game::Game(const char* title, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	running = true;
}

void Game::clear(int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
}

void Game::present() {
	SDL_RenderPresent(renderer);
}

void Game::render(SDL_Texture* texture, SDL_Rect* rect) {
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

void Game::renderWithRotation(SDL_Texture* texture, SDL_Rect* rect, float angle) {
	SDL_RenderCopyEx(renderer, texture, NULL, rect, angle, NULL, SDL_FLIP_NONE);
}

void Game::renderFlipped(SDL_Texture* texture, SDL_Rect* rect, bool flip) {
	if (flip) {
		SDL_RenderCopyEx(renderer, texture, NULL, rect, NULL, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer, texture, NULL, rect, NULL, NULL, SDL_FLIP_NONE);
	}
}

void Game::events(bool &pause, bool &mouse_pressed) {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
			pause = !pause;
			break;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			mouse_pressed = true;
		}
		else {
			mouse_pressed = false;
		}
	}
}

void Game::quit() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}