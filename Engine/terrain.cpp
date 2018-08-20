#include "meshloader.hpp"
#include "textureloader.hpp"
#include <vector>
#include "terrain.hpp"

Terrain::Terrain() {

}

Terrain::Terrain(glm::vec3 pos, int size, std::string heightmap, std::shared_ptr<Texture> texture) {
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
