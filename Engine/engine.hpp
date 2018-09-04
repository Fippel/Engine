#pragma once

#include "window.hpp"
#include "shaderprogram.hpp"
#include "glrenderer.hpp"
#include "textureloader.hpp"
#include "meshloader.hpp"
#include "glframebuffer.hpp"
#include "camera.hpp"
#include "batch.hpp"
#include <memory>


class Engine {
private:
	static Engine* _instance;
	std::unique_ptr<Window> _window;
	std::unique_ptr<GLRenderer> _renderer;
	std::unique_ptr<MeshLoader> _meshLoader;
	std::unique_ptr<TextureLoader> _textureLoader;
	std::shared_ptr<Texture> _testTexture;
	std::shared_ptr<Texture> _waterTexture; // temp... ändra så att meshes har egna texturer
	std::shared_ptr<GLFrameBuffer> _deferredFBO;
	GLFrameBuffer* _waterFBO;
	ShaderProgram* _geometryPass;
	ShaderProgram* _lightingPass;
	ShaderProgram* _waterPass;

	Camera _camera;
	std::vector<Model> _models;
	std::vector<Model> _waters;
	std::vector<Terrain> _terrains;

	Batch* _testBatch;

	void _init();
	void _initSDL();
	void _initGL();
	void _initWorld();


public:
	Engine();
	~Engine() {
		delete _instance;
	}

	static Engine* getInstance() {
		if (!_instance)
			_instance = new Engine();

		return _instance;
	}

	Window* getWindow() { return _window.get(); }
	GLRenderer* getRenderer() { return _renderer.get(); }
	MeshLoader* getMeshLoader() { return _meshLoader.get(); }
	TextureLoader* getTextureLoader() { return _textureLoader.get(); }
	int run();
};
