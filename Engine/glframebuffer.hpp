#pragma once

#include <map>
#include <memory>
#include "gltexture.hpp"

class GLFrameBuffer {
private:
	unsigned int _fbo;
	std::map<unsigned int, std::shared_ptr<Texture>> _textures;
	std::shared_ptr<Texture> _depth;
public:
	GLFrameBuffer();
	virtual ~GLFrameBuffer();
	GLFrameBuffer& addTexture(unsigned int key, std::shared_ptr<Texture> texture);
	GLFrameBuffer& addTexture(unsigned int key, Texture::TextureFormat type, unsigned int x, unsigned int y);
	GLFrameBuffer& addDepth(unsigned int key, unsigned int x, unsigned int y);
	Texture getTexture(int index);
	int getNumberOfTextures();
	GLFrameBuffer& bind();
	GLFrameBuffer& bindDepth(unsigned int key);
	inline std::shared_ptr<Texture>& operator[](size_t key) {
		return _textures[key];
	}
	void finalize();
};
