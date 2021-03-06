#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <memory>
#include "shaderprogram.hpp"
#include "window.hpp"
#include "mesh.hpp"
#include "terrain.hpp"
#include "batch.hpp"

class GLRenderer {
private:
	SDL_GLContext _context;
	GLuint _emptyVAO;
	Mesh* _fullscreenQuad;
public:
	GLRenderer(SDL_Window* window);
	~GLRenderer();
	void render(Window* window, ShaderProgram* shader);
	void render(Window* window, std::vector<Model>& models, ShaderProgram* shader);
	void render(Window* window, std::vector<Terrain>& terrains, ShaderProgram* shader);
	void renderWater(Window* window, std::vector<Model>& waters, ShaderProgram* shader);

	static void APIENTRY openglCallbackFunction(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	) {
		(void)source; (void)type; (void)id;
		(void)severity; (void)length; (void)userParam;
		switch (severity) {
		case GL_DEBUG_SEVERITY_LOW:
			printf("GL CALLBACK::LOW SEVERITY ");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			printf("GL CALLBACK::MEDIUM SEVERITY ");
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			printf("GL CALLBACK::HIGH SEVERITY ");
			break;
		}

		if(severity != GL_DEBUG_SEVERITY_NOTIFICATION)
			fprintf(stderr, "%s\n", message);

		//printf("%s\n, ");
		if (severity == GL_DEBUG_SEVERITY_HIGH) {
			fprintf(stderr, "Aborting...\n");
			//abort();
		}
	}
};
