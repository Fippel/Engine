#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include "gltexture.hpp"
#include "mesh.hpp"
#include <map>

class freetype {
private:
	FT_Library _ft;
	FT_Face _face; // font
	struct Character {
		GLuint textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
	};
	std::map<GLchar, Character> _characters;
	GLuint _VAO, _VBO;
public:
	void initFreetype();
	void setupBuffers();
	void loadCharacters();
	Model generateText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};







