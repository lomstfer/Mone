#include "Text.hpp"

Text::Text(std::string text, int size, SDL_Color color, std::string fontpath, int x, int y, bool centered, SDL_Renderer* renderer)
	: text(text), size(size), color(color), fontpath(fontpath), x(x), y(y), renderer(renderer), centered(centered)
{
	font = TTF_OpenFont(fontpath.c_str(), size);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
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
	/*font = TTF_OpenFont(fontpath.c_str(), size);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (centered)
		rect.x = x - rect.w / 2;
	else
		rect.x = x;
	rect.y = y;*/


	//SDL_FreeSurface(surface);

	// Pixels from our text
	surface = TTF_RenderText_Solid(font, text.c_str(), color);

	// Setup the texture
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	// Free the surface
	// We are done with it after we have uploaded to
	// the texture
	SDL_FreeSurface(surface);

	// Create a rectangle to draw on
	rect.x = x;
	rect.y = y;
	// Render our text on a rect
	SDL_RenderCopy(renderer, texture, NULL, &rect);

}

Text::~Text() {
	// Destroy our textured text
	SDL_DestroyTexture(texture);

	// Close our font subsystem
	TTF_CloseFont(font);
}
