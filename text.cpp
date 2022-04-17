#include "Text.hpp"

Text::Text(std::string text, int size, SDL_Color color, std::string fontpath, int x, int y, bool centered, SDL_Renderer* renderer)
	: text(text), size(size), color(color), fontpath(fontpath), x(x), y(y), renderer(renderer), centered(centered)
{
	font = TTF_OpenFont(fontpath.c_str(), size);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (centered)
		rect.x = x - rect.w / 2;
	else
		rect.x = x;
	rect.y = y;
}

void Text::render()
{
	
}

void Text::update()
{
	font = TTF_OpenFont(fontpath.c_str(), size);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (centered)
		rect.x = x - rect.w / 2;
	else
		rect.x = x;
	rect.y = y;

	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
