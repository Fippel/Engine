#include "textdata.hpp"
#include "glm/glm.hpp"

void freetype::initFreetype() {
		if (FT_Init_FreeType(&_ft))
			printf("ERROR::FREETYPE: Could not init FreeType Library\n");

		if (FT_New_Face(_ft, "assets/fonts/arial.ttf", 0, &_face))
			printf("ERROR::FREETYPE: Failed to load font\n");
		FT_Set_Pixel_Sizes(_face, 0, 48);

		if (FT_Load_Char(_face, 'X', FT_LOAD_RENDER))
			printf("ERROR::FREETYTPE: Failed to load Glyph\n");
		
}

void freetype::setupBuffers() {
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void freetype::loadCharacters() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < 128; i++) {
		if(FT_Load_Char(_face, i, FT_LOAD_RENDER)) {
			printf("ERROR::FREETYTPE: Failed to load Glyph\n");
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			_face->glyph->bitmap.width,
			_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			_face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
			glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
			_face->glyph->advance.x
		};
		_characters.insert(std::pair<GLchar, Character>(i, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(_face);
	FT_Done_FreeType(_ft);
}
Model freetype::generateText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
	Model m;
	
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = _characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		std::vector<Mesh::Vertex> vertices;
		Mesh::Vertex v;
		v.pos = glm::vec3(xpos, ypos + h, 0);
		v.normal = glm::vec3(0, 0, -1);
		v.uv = glm::vec2(0.0, 0.0);
		v.color = color;
		vertices.push_back(v);

		v.pos = glm::vec3(xpos, ypos, 0);
		v.normal = glm::vec3(0, 0, -1);
		v.uv = glm::vec2(0.0, 1.0);
		v.color = color;
		vertices.push_back(v);

		v.pos = glm::vec3(xpos + w, ypos, 0);
		v.normal = glm::vec3(0, 0, -1);
		v.uv = glm::vec2(1.0, 1.0);
		v.color = color;
		vertices.push_back(v);

		v.pos = glm::vec3(xpos + w, ypos + h, 0);
		v.normal = glm::vec3(0, 0, -1);
		v.uv = glm::vec2(1.0, 0.0);
		v.color = color;
		vertices.push_back(v);

		std::vector<GLuint> indices{1, 0, 3, 3, 2, 1};


		std::map<std::string, Texture> tmpMap;
		tmpMap["diffuseTexture"] = Texture(_characters[*c].textureID);
		m.meshes.push_back(new Mesh(vertices, indices, tmpMap, false));

		//{ xpos,	  ypos + h,	  0.0, 0.0 },
		//
		//{ xpos,     ypos,       0.0, 1.0 },
		//
		//{ xpos + w, ypos,       1.0, 1.0 },
		//
		//{ xpos + w, ypos + h,   1.0, 0.0 }
		x += (ch.advance >> 6) * scale;
	}
	return m;

	
}
void freetype::render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
	

}
