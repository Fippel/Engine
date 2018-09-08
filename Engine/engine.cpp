#include "engine.hpp"
#include "terrain.hpp"
#include "SDL2/SDL.h"

Engine* Engine::_instance;

void Engine::_init() {
	_initSDL();
	_initGL();
	
	_meshLoader = std::make_unique<MeshLoader>();
	_textureLoader = std::make_unique<TextureLoader>();

	_geometryPass = new ShaderProgram("Geometry Pass");
	_geometryPass->attachShader(ShaderProgram::ShaderType::VertexShader, "assets/shaders/geometryPass.vert")
		.attachShader(ShaderProgram::ShaderType::FragmentShader, "assets/shaders/geometryPass.frag")
		.finalize();

	_lightingPass = new ShaderProgram("Lighting Pass");
	_lightingPass->attachShader(ShaderProgram::ShaderType::VertexShader, "assets/shaders/lightingPass.vert")
		.attachShader(ShaderProgram::ShaderType::FragmentShader, "assets/shaders/lightingPass.frag")
		.finalize();

	_waterPass = new ShaderProgram("Water Pass");
	_waterPass->attachShader(ShaderProgram::ShaderType::VertexShader, "assets/shaders/waterPass.vert")
		.attachShader(ShaderProgram::ShaderType::FragmentShader, "assets/shaders/waterPass.frag")
		.finalize();

	_initWorld();
}

void Engine::_initSDL() {
	_window = std::make_unique<Window>("Engine test");
}

void Engine::_initGL() {
	_renderer = std::make_unique<GLRenderer>(_window->getWindow());
}

void Engine::_initWorld() {
	_testTexture = _textureLoader->loadTexture("assets/textures/grass.png");
	_waterTexture = _textureLoader->loadTexture("assets/textures/water.png");

	_testBatch = new Batch();
	_testBatch->createPipeline("assets/shaders/geometryPass.vert", "assets/shaders/geometryPass.frag");
	_testBatch->addTexture(Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight());
	_testBatch->addTexture(Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight());
	_testBatch->addTexture(Texture::TextureFormat::RGBA32f, _window->getWidth(), _window->getHeight());
	_testBatch->addDepthTexture(_window->getWidth(), _window->getHeight());
	_testBatch->FBOFinalize();
	_testBatch->setTextureIndices(6, 0, 0, 0);
	_testBatch->addInput(1, _camera.getView());
	_testBatch->addInput(2, _camera.getProj(_window.get()->getSizes()));
	_testBatch->addInput(25, new int(6));
	
	_waterFBO = new GLFrameBuffer();
	_waterFBO->bind()
		.addTexture(0, Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight())
		.addTexture(1, Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight())
		.addTexture(2, Texture::TextureFormat::RGBA32f, _window->getWidth(), _window->getHeight())
		.addDepth(3, _window->getWidth(), _window->getHeight())
		.finalize();

	_deferredFBO = std::shared_ptr<GLFrameBuffer>(new GLFrameBuffer());
	_deferredFBO->bind()
		.addTexture(0, Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight())
		.addTexture(1, Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight())
		.addTexture(2, Texture::TextureFormat::RGBA32f, _window->getWidth(), _window->getHeight())
		.addDepth(3, _window->getWidth(), _window->getHeight())
		.finalize();
	//
	//_waterFBO = std::shared_ptr<GLFrameBuffer>(new GLFrameBuffer());
	//_waterFBO->bind()
	//	.addTexture(0, Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight()) // Reflection
	//	.addTexture(1, Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight()) // Refraction
	//	.addDepth(2, _window->getWidth(), _window->getHeight())
	//	.finalize();
	//
	////_models.back().updateModelMatrix(glm::vec3(0, 0, 0), glm::vec3(0.3f));
	//_models.push_back(Terrain(glm::vec3(0, -10, 0), 100, "assets/textures/heightmap5.bmp", _textureLoader->loadTexture("assets/textures/grass.png")).getModel());
	_terrains.push_back(Terrain(glm::vec3(0, -10, 0), 100, "assets/textures/heightmap5.bmp", _textureLoader->loadTexture("assets/textures/grass.png")));
	//_waters.push_back(Terrain(glm::vec3(10, -3, 10), 80, "", nullptr).getModel());
	//_models.push_back(_meshLoader->loadTerrain(100, "assets/textures/heightmap5.bmp", "assets/textures/grass.png", glm::vec3(0.f, -10.f, 0.f)));
	//_models.push_back(_meshLoader->loadTerrain(80, "", "assets/textures/water.png", glm::vec3(10, -3, 10)));
	//_waters.push_back(_meshLoader->loadTerrain(80, "", "", glm::vec3(10, -3, 10)));
	_camera.position = glm::vec3(0, 0, 0);
}

Engine::Engine() {

}

int Engine::run() {
	_init();

	SDL_Event event;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime;

	bool quit = false;

	while (!quit) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_LSHIFT:
				_camera.pressedShift = true;
				break;
			case SDLK_SPACE:
				_camera.moveUp = true;
				break;
			case SDLK_w:
				_camera.moveForward = true;
				break;
			case SDLK_a:
				_camera.moveLeft = true;
				break;
			case SDLK_s:
				_camera.moveBack = true;
				break;
			case SDLK_d:
				_camera.moveRight = true;
				break;
			case SDLK_LALT:
				if (_camera.counter >= 1.f) {
					_camera.enableMouse = !_camera.enableMouse;
					SDL_ShowCursor(_camera.enableMouse);
					_camera.counter = 0.f;
				}
				break;
			default:
				break;
			}

			switch (event.type) {
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_LSHIFT)
					_camera.pressedShift = false;
				if (event.key.keysym.sym == SDLK_SPACE)
					_camera.moveUp = false;
				if (event.key.keysym.sym == SDLK_LCTRL)
					_camera.moveDown = false;
				if (event.key.keysym.sym == SDLK_w)
					_camera.moveForward = false;
				if (event.key.keysym.sym == SDLK_a)
					_camera.moveLeft = false;
				if (event.key.keysym.sym == SDLK_s)
					_camera.moveBack = false;
				if (event.key.keysym.sym == SDLK_d)
					_camera.moveRight = false;
				break;
			default:
				break;
			}
		}

		_camera.update(deltaTime, _terrains[0].getHeight(_camera.position.x, _camera.position.z), _window.get());

		{	//Geometry pass
			//glEnable(GL_CLIP_DISTANCE0);
			//_geometryPass->useProgram();
			//_geometryPass->setValue(0, _models[0].model);
			//_geometryPass->setValue(1, _camera.getView());
			//_geometryPass->setValue(2, _camera.getProj());
			//_geometryPass->setValue(25, 6);
			////_testTexture->bind(6);
			//_waterFBO->bind();
			//
			//
			//_renderer->render(_window.get(), _models, _geometryPass);
			//_renderer->render(_window.get(), _terrains, _geometryPass);
			//_renderer->renderWater(_window.get(), _waters, _waterPass);

			
			_camera.getView();
			_camera.getProj(_window.get()->getSizes());
			_testBatch->render(_window.get());
		}

		//{	// Water pass
		//	_waterPass->useProgram();
		//	_waterPass->setValue(1, _camera.getView());
		//	_waterPass->setValue(2, _camera.getProj());
		//	_waterPass->setValue(25, 6);
		//	_deferredFBO->bind();
		//	//_waterFBO->bind();
		//	_renderer->renderWater(_window.get(), _waters, _waterPass);
		//}

		{	//Lighting pass
			_lightingPass->useProgram();
			_lightingPass->setValue(20, 0);
			_lightingPass->setValue(21, 1);
			_lightingPass->setValue(22, 2);
			_lightingPass->setValue(23, 3);
			//_lightingPass->setValue(24, 4);
			(*(_testBatch->getFBO()))[0]->bind(0);
			(*(_testBatch->getFBO()))[1]->bind(1);
			(*(_testBatch->getFBO()))[2]->bind(2);
			_testBatch->getFBO()->bindDepth(3);
			//(*_waterFBO)[0]->bind(0);
			//(*_waterFBO)[1]->bind(1);
			//(*_waterFBO)[2]->bind(2);
			//_waterFBO->bindDepth(3);
			//_testTexture->bind(4);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			_renderer->render(_window.get(), _lightingPass);
		}

		SDL_GL_SwapWindow(_window->getWindow());
	}

	return 0;
}