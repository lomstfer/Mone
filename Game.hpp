#include <SDL.h>
#include <SDL_image.h>

class Game {
public:
	Game(const char* title, int width, int height);

	SDL_Renderer* renderer;
	SDL_Window* window;

public:
	bool running;
	SDL_Event event;

	void clear(int r, int g, int b);
	void present();

	void loadTexture(const char* filepath);
	void render(SDL_Texture* texture, SDL_Rect* rect);
	void renderWithRotation(SDL_Texture* texture, SDL_Rect* rect, float angle);
	void renderFlipped(SDL_Texture* texture, SDL_Rect* rect, bool flip);

	void events(bool& mouse_pressed, int& mouse_x, int& mouse_y);
	void quit();
};