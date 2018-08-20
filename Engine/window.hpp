#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <glm/glm.hpp>

class Window {
private:
	int _width = 1280;
	int _height = 720;
	bool _fullscreen = 0;
	SDL_Window* _window;
	std::string _title;

public:
	Window(const std::string& title = "Test");
	~Window();
	SDL_Window* getWindow() { return _window; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	glm::ivec2 getSizes() { return glm::ivec2(_width, _height); }
};
