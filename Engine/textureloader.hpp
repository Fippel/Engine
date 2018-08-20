#pragma once

#include <string>
#include <memory>
#include <map>
#include "gltexture.hpp"

class TextureLoader {
private:
	std::map<std::string, std::shared_ptr<Texture>> _loadedTextures;
public:
	TextureLoader();
	~TextureLoader();
	std::shared_ptr<Texture> loadTexture(const std::string& path);
};
