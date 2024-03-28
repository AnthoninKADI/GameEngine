#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void drawRect(const Rectangle& rect);
	void drawPaddle(const Rectangle& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void endDraw();
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
};

