#include "gameengine.hpp"
#include "meshloader.hpp"
#include "glrenderer.hpp"
#include "camera.hpp"

#include "gamecontroller.hpp"

void GameEngine::_initialize() {
	Entity* e = new Entity("GameController");
	e->setup(0, _eh, _bh, _fl);
	GameController* gc = new GameController();
	e->addComponent(gc);
	_eh->add(e);

}

GameEngine::GameEngine() {
	_bh = new BatchHandler();
	_fl = new FileLoader();
	_eh = new EntityHandler(_bh, _fl);
	_window = new Window("Meow"); // NAMN PLOX :D

	_client.initialize("localhost", 123);

	std::make_unique<GLRenderer>(_window->getWindow());
}

GameEngine::~GameEngine() {
	delete _bh;
	delete _window;
}


void GameEngine::run() {


	Camera c;
	c.position = glm::vec3(0, 0, 0);

	//TEST
	//SETUP SHIT

	Batch* b = new Batch();
	Batch* lightingPass = new Batch();
	Model quad;
	{
		b->createPipeline("../Engine/assets/shaders/geometryPass.vert", "../Engine/assets/shaders/geometryPass.frag");
		b->addTexture(Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight());
		b->addTexture(Texture::TextureFormat::RGB32f, _window->getWidth(), _window->getHeight());
		b->addTexture(Texture::TextureFormat::RGBA32f, _window->getWidth(), _window->getHeight());
		b->addDepthTexture(_window->getWidth(), _window->getHeight());
		b->FBOFinalize();
		b->setTextureIndices(6, 0, 0, 0);
		b->addInput(1, c.getView());
		b->addInput(2, c.getProj(_window->getSizes()));
		b->addInput(25, new int(6));

		//b->registerModel(&m);

		_bh->addBatch(b, "TESTBITCH", 2);



		lightingPass->createPipeline("../Engine/assets/shaders/lightingPass.vert", "../Engine/assets/shaders/lightingPass.frag");
		quad.meshes.push_back(_fl->getML()->getQuad());
		lightingPass->registerModel(&quad);
		lightingPass->addInput(20, new int(0));
		lightingPass->addInput(21, new int(1));
		lightingPass->addInput(22, new int(2));
		lightingPass->addInput(23, new int(3));
		GLFrameIndex gfi;
		gfi.buffer = b->getFBO();
		gfi.texturePos.push_back(0);
		gfi.bindPos.push_back(0);
		gfi.isDepth.push_back(false);
		gfi.texturePos.push_back(1);
		gfi.bindPos.push_back(1);
		gfi.isDepth.push_back(false);
		gfi.texturePos.push_back(2);
		gfi.bindPos.push_back(2);
		gfi.isDepth.push_back(false);

		gfi.isDepth.push_back(true);
		gfi.texturePos.push_back(3);
		gfi.bindPos.push_back(3);

		lightingPass->addFBOInput(gfi);

		_bh->addBatch(lightingPass, "Lighting Pass", 10);
	}



	SDL_Event event;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0.0f;

	bool quit = false;

	_initialize();

	while( !quit ) {

		_eh->update(deltaTime);

		c.getView();
		c.update(deltaTime, 1, _window);
		//b->render(_window);
		//lightingPass->render(_window);
		_bh->render(_window);

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;

		while( SDL_PollEvent(&event) ) {
			if( event.type == SDL_QUIT )
				quit = true;

			switch( event.key.keysym.sym ) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_LSHIFT:
				c.pressedShift = true;
				break;
			case SDLK_SPACE:
				c.moveUp = true;
				break;
			case SDLK_w:
				c.moveForward = true;
				break;
			case SDLK_a:
				c.moveLeft = true;
				break;
			case SDLK_s:
				c.moveBack = true;
				break;
			case SDLK_d:
				c.moveRight = true;
				break;
			case SDLK_LALT:
				if( c.counter >= 1.f ) {
					c.enableMouse = !c.enableMouse;
					SDL_ShowCursor(c.enableMouse);
					c.counter = 0.f;
				}
				break;
			default:
				break;
			}

			switch( event.type ) {
			case SDL_KEYUP:
				if( event.key.keysym.sym == SDLK_LSHIFT )
					c.pressedShift = false;
				if( event.key.keysym.sym == SDLK_SPACE )
					c.moveUp = false;
				if( event.key.keysym.sym == SDLK_LCTRL )
					c.moveDown = false;
				if( event.key.keysym.sym == SDLK_w )
					c.moveForward = false;
				if( event.key.keysym.sym == SDLK_a )
					c.moveLeft = false;
				if( event.key.keysym.sym == SDLK_s )
					c.moveBack = false;
				if( event.key.keysym.sym == SDLK_d )
					c.moveRight = false;
				break;
			default:
				break;
			}
			
		}


		SDL_GL_SwapWindow(_window->getWindow());
	}

	//TEST
}