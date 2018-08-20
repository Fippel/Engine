#include "gltexture.hpp"

Texture::Texture() {

}

Texture::Texture(const TextureFormat format, glm::vec2 size) {
	_format = format;
	_size = size;
	_setData(nullptr);
}

Texture::Texture(const std::string& path) {
	_path = path;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if(!surface)
		printf("Texture %s failed to load! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	else {
		SDL_Surface* newSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
		if(!newSurface)
			printf("Unknown pixelformat. SDL_image Error: %s\n", SDL_GetError());
		else {
			SDL_FreeSurface(surface);
			surface = newSurface;
			_format = TextureFormat::RGBA8;
			_size = glm::vec2(surface->w, surface->h);
			_setData(surface->pixels);
			SDL_FreeSurface(surface);
		}
	}
}

Texture::~Texture() {

}