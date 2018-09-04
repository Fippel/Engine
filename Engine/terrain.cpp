#include "meshloader.hpp"
#include "textureloader.hpp"
#include <vector>
#include "terrain.hpp"
#include <cmath>

Terrain::Terrain() {

}

Terrain::Terrain(glm::vec3 pos, int size, std::string heightmap, std::shared_ptr<Texture> texture) {
	_x = pos.x * size;
	_z = pos.z * size;
	_size = size;
	SDL_Surface* surface = nullptr;
	std::map<std::string, Texture> textures;
	if (texture)
		textures["diffuseTexture"] = (*texture); // (*loadTexture(texturePath).get());

	int vertexCountW = 200;
	int vertexCountH = 200;
	if (heightmap != "") {
		surface = IMG_Load(heightmap.c_str());
		vertexCountW = surface->w;
		vertexCountH = surface->h;
	}
	_vertexCountW = vertexCountW;
	_vertexCountW = vertexCountH;
	int count = vertexCountW * vertexCountH;
	std::vector<Mesh::Vertex> vertices;
	Mesh::Vertex tmp;
	std::vector<GLuint> indices(6 * (vertexCountW - 1)*(vertexCountH - 1));
	Uint32 pixel;
	int heightMultiplier = 10;
	_heights = new float*[vertexCountW];

	for (int i = 0; i < vertexCountW; i++) {
		_heights[i] = new float[vertexCountH];
		for (int j = 0; j < vertexCountH; j++) {
			float y = 0;
			if (surface) {
				pixel = _getPixel(surface, i, j);
				Uint8 r, g, b;
				SDL_GetRGB(pixel, surface->format, &r, &g, &b);
				y = (float)r / 255.0;
				y = (y * heightMultiplier) + pos.y;
			}
			else
				y = pos.y;
			_heights[i][j] = y;
			tmp.pos = glm::vec3(((float)j / ((float)vertexCountW - 1) * size) + pos.x, y, ((float)i / ((float)vertexCountH - 1) * size) + pos.z);
			tmp.normal = glm::vec3(0, 1, 0);
			tmp.uv = glm::vec2((float)j / ((float)vertexCountW - 1) * 20, (float)i / ((float)vertexCountH - 1) * 20);
			vertices.push_back(tmp);
		}
	}

	int pointer = 0;
	for (int gz = 0; gz<vertexCountW - 1; gz++) {
		for (int gx = 0; gx<vertexCountH - 1; gx++) {
			int topLeft = (gz*vertexCountW) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*vertexCountW) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomRight;
		}
	}

	if (!texture) 
		_model.meshes.push_back(new Mesh(vertices, indices, false));
	
	_model.meshes.push_back(new Mesh(vertices, indices, textures, false));
}

Terrain::~Terrain() {

}

float Terrain::getHeight(float worldX, float worldZ) {
	float terrainX = worldX - _x;
	float terrainZ = worldZ - _z;
	float gridSquareSize = _size / ((float)_vertexCountW - 1);
	int gridX = (int)std::floor(terrainX / gridSquareSize);
	int gridZ = (int)std::floor(terrainZ / gridSquareSize);
	if (gridX >= _vertexCountW - 1 || gridZ >= _vertexCountW - 1 || gridX < 0 || gridZ < 0)
		return 0;
	float xCoord = std::fmod(terrainX, gridSquareSize);
	xCoord /= gridSquareSize;
	float zCoord = std::fmod(terrainZ, gridSquareSize);
	zCoord /= gridSquareSize;
	float answer;
	if (xCoord <= (1 - zCoord)) {
		answer = _barryCentric(glm::vec3(0, _heights[gridX][gridZ], 0),
			glm::vec3(1, _heights[gridX + 1][gridZ], 0),
			glm::vec3(0, _heights[gridX][gridZ + 1], 1),
			glm::vec2(xCoord, zCoord));
	}
	else {
		answer = _barryCentric(glm::vec3(1, _heights[gridX + 1][gridZ], 0),
			glm::vec3(1, _heights[gridX + 1][gridZ + 1], 1),
			glm::vec3(0, _heights[gridX][gridZ + 1], 1),
			glm::vec2(xCoord, zCoord));
	}

	return answer;
	//return _heights[(int)worldX][(int)worldZ];
}
