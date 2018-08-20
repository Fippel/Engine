#pragma once

#include "meshloader.hpp"

class Terrain {
private:
	Model _model;
	float _x;
	float _z;
	float** _heights;

	Uint32 _getPixel(SDL_Surface *surface, int x, int y) {
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		return *(Uint32*)p;
	}
public:
	Terrain();
	Terrain(glm::vec3 pos, int size, std::string heightmap, std::shared_ptr<Texture> texture);
	~Terrain();

	Model getModel() {
		return _model;
	}
};
