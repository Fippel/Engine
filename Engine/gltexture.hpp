#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <SDL2/SDL_image.h>
#include <string>

class Texture {
public:
	const enum TextureFormat : const int {
		R8 = 0,
		RG8,
		RGB8,
		RGBA8,

		R16f,
		RG16f,
		RGB16f,
		RGBA16f,

		R32f,
		RG32f,
		RGB32f,
		RGBA32f,

		Depth16f,
		Depth24f,
		Depth32f
	};

	static GLenum toGLInternal(TextureFormat type) {
		static const GLenum translate[] = {
			GL_RED,
			GL_RG,
			GL_RGB,
			GL_RGBA,

			GL_R16F,
			GL_RG16F,
			GL_RGB16F,
			GL_RGBA16F,

			GL_R32F,
			GL_RG32F,
			GL_RGB32F,
			GL_RGBA32F,

			GL_DEPTH_COMPONENT16,
			GL_DEPTH_COMPONENT24,
			GL_DEPTH_COMPONENT32
		};
		return translate[static_cast<int>(type)];
	}

	static GLenum toGLBase(TextureFormat type) {
		static const GLenum translate[] = {
			GL_RED,
			GL_RG,
			GL_RGB,
			GL_RGBA,

			GL_RED,
			GL_RG,
			GL_RGB,
			GL_RGBA,

			GL_RED,
			GL_RG,
			GL_RGB,
			GL_RGBA,

			GL_DEPTH_COMPONENT,
			GL_DEPTH_COMPONENT,
			GL_DEPTH_COMPONENT
		};
		return translate[static_cast<int>(type)];
	}

	static GLenum toGLDataType(TextureFormat format) {
		static const GLenum translate[] = {
			GL_UNSIGNED_BYTE,
			GL_UNSIGNED_BYTE,
			GL_UNSIGNED_BYTE,
			GL_UNSIGNED_BYTE,

			GL_FLOAT,
			GL_FLOAT,
			GL_FLOAT,
			GL_FLOAT,

			GL_FLOAT,
			GL_FLOAT,
			GL_FLOAT,
			GL_FLOAT,

			GL_FLOAT,
			GL_FLOAT,
			GL_FLOAT
		};
		return translate[format];
	}

private:
	GLuint _texture;
	glm::ivec2 _size;
	TextureFormat _format;
	std::string _path;

	void _setData(void* pixels) {
		glGenTextures(1, &_texture);
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);

		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, toGLInternal(_format), _size.x, _size.y, 0, toGLBase(_format), toGLDataType(_format), pixels);
	}
public:
	Texture();
	Texture(GLuint texID);
	Texture(const TextureFormat format, glm::vec2 size);
	Texture(const std::string& path);
	~Texture();

	void setData(const glm::ivec2& size, void* data, glm::ivec2 offset = glm::ivec2(0)) {
		glTextureSubImage2D(_texture, 0, offset.x, offset.y, size.x, size.y, static_cast<GLenum>(_format), toGLDataType(_format), data);
	}

	void bind(size_t pos) {
		glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + pos));
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	unsigned int getLocation() { return _texture; }
};
