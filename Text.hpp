#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
    int size;
    SDL_Color color;
    std::string fontpath;
    int x;
    int y;
    bool centered;
    SDL_Renderer* renderer;
    std::string text;
    TTF_Font* font;
	SDL_Rect rect;
	SDL_Surface* surface;
	SDL_Texture* texture;
    Text(std::string text, int size, SDL_Color color, std::string fontpath, int x, int y, bool centered, SDL_Renderer* renderer);
    void render();
    void update();
    void updateFont(std::string fontpath);
    ~Text();
};