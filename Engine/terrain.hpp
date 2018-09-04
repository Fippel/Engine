#pragma once

#include "meshloader.hpp"

class Terrain {
private:
	Model _model;
	float _x;
	float _z;
	float** _heights;
	int _size;
	int _vertexCountW;
	int _vertexCountH;

	inline double _fRand(double fMin, double fMax)
	{
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

	Uint32 _getPixel(SDL_Surface *surface, int x, int y) {
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		return *(Uint32*)p;
	}

	float _barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
public:
	Terrain();
	Terrain(glm::vec3 pos, int size, std::string heightmap, std::shared_ptr<Texture> texture);
	~Terrain();

	Model getModel() {
		return _model;
	}

	float getX() {
		return _x;
	}

	float getZ() {
		return _z;
	}

	float getHeight(float worldX, float worldZ);
};
