#include "Text.hpp"

Text::Text(std::string text, int size, SDL_Color color, std::string fontpath, int x, int y, bool centered, SDL_Renderer* renderer)
	: text(text), size(size), color(color), fontpath(fontpath), x(x), y(y), renderer(renderer), centered(centered)
{
	font = TTF_OpenFont(fontpath.c_str(), size);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	if (centered)
		rect.x = x - rect.w / 2;
	else
		rect.x = x;
	rect.y = y;
}

void Text::render()
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::update()
{
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	if (centered)
		rect.x = x - rect.w / 2;
	else
		rect.x = x;
	rect.y = y;
}

void Text::updateFont(std::string fontpath) {
	TTF_CloseFont(font);
	font = TTF_OpenFont(fontpath.c_str(), size);
}

Text::~Text() {
	// Destroy our textured text
	SDL_DestroyTexture(texture);

	// Close our font subsystem
	TTF_CloseFont(font);
}
