#pragma once

#include <glad/glad.h>
#include <string>
#include "mesh.hpp"
#include <memory>
#include <map>

class MeshLoader {
private:
	Uint32 _getPixel(SDL_Surface *surface, int x, int y) {
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		return *(Uint32*)p;
	}
public:
	MeshLoader();
	~MeshLoader();
	std::map<std::string, std::shared_ptr<Texture>> _loadedTextures;
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene, Model& models);
	Model* loadMesh(const char* path, bool hasModelMX);
	std::shared_ptr<Texture> loadTexture(const std::string& path);
	//GLint textureFromFile(const char* path, std::string directory);
	std::map<std::string, Texture> loadMaterialTextures(aiMaterial* mtl, aiTextureType type, std::string typeName);
	Mesh* getQuad();
};
