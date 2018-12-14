#include "gameengine.hpp"
#include "meshloader.hpp"
#include "glrenderer.hpp"
#include "camera.hpp"
#include "textcomponent.hpp"

#include "gamecontroller.hpp"



void GameEngine::_initialize() {
	Entity* e = new Entity("GameController");
	e->setup(0);
	GameController* gc = new GameController();
	e->addComponent(gc);
	TextComponent* tc = new TextComponent();
	e->addComponent(tc);

	_eh->add(e);
	
	

}

GameEngine::GameEngine() {
	//_bh = new BatchHandler();
	_bh = BatchHandler::getInstance();
	_fl = FileLoader::getInstance();
	_eh = EntityHandler::getInstance();
	_window = new Window("Meow"); // NAMN PLOX :D
	ft = freetype::getInstance();
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

	ft->initFreetype();
	ft->setupBuffers();
	ft->loadCharacters();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Batch* b = new Batch();
	Batch* lightingPass = new Batch();
	Batch* textPass = new Batch();
	Batch* finalPass = new Batch();
	Model quad;
	Model tmpm = ft->generateText("aldrig att detta kommer funka", 100, 200, 1.0, glm::vec3(1, 0, 0));
	Model tmpmp = ft->generateText("nu skriver jag en till grej", 100, 400, 1.0, glm::vec3(1, 0, 0));
	{
		b->createPipeline("assets/shaders/geometryPass.vert", "assets/shaders/geometryPass.frag");
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

		textPass->createPipeline("assets/shaders/textPass.vert", "assets/shaders/textPass.frag");
		textPass->addTexture(Texture::TextureFormat::RGBA32f, _window->getWidth(), _window->getHeight());
		textPass->FBOFinalize();
		glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
		textPass->addInput(33, &projection);
		textPass->addInput(20, new int(9));
		//textPass->addInput(21, new int(10));
		textPass->setTextureIndices(9, 0, 0, 0);

		//GLFrameIndex gfi;
		//gfi.buffer = lightingPass->getFBO();
		//gfi.texturePos.push_back(0);
		//gfi.bindPos.push_back(10);
		//gfi.isDepth.push_back(false);


		_bh->addBatch(textPass, "Text Pass", 7);
		//textPass->registerModel(&quad);
		textPass->registerModel(&tmpm);
		textPass->registerModel(&tmpmp);

		lightingPass->createPipeline("assets/shaders/lightingPass.vert", "assets/shaders/lightingPass.frag");
		//lightingPass->addTexture(Texture::TextureFormat::RGBA32f, _window->getWidth(), _window->getHeight());
		//lightingPass->FBOFinalize();
		quad.meshes.push_back(_fl->getML()->getQuad());
		lightingPass->registerModel(&quad);
		lightingPass->addInput(20, new int(0));
		lightingPass->addInput(21, new int(1));
		lightingPass->addInput(22, new int(2));
		lightingPass->addInput(23, new int(3));
		lightingPass->addInput(25, new int(5));

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

		GLFrameIndex textGfi;
		textGfi.buffer = textPass->getFBO();
		textGfi.texturePos.push_back(0);
		textGfi.bindPos.push_back(5);
		textGfi.isDepth.push_back(false);

		lightingPass->addFBOInput(textGfi);

		lightingPass->clearFlag = false;
		_bh->addBatch(lightingPass, "Lighting Pass", 10);

		//finalPass->createPipeline("assets/shaders/finalPass.vert", "assets/shaders/finalPass.frag");
		//finalPass->registerModel(&quad);
		//finalPass->addInput(20, new int(0));
		//finalPass->addInput(21, new int(1));
		//
		//GLFrameIndex textGfi;
		//textGfi.buffer = textPass->getFBO();
		//textGfi.texturePos.push_back(0);
		//textGfi.bindPos.push_back(1);
		//textGfi.isDepth.push_back(false);
		//
		//finalPass->addFBOInput(textGfi);
		//
		//GLFrameIndex lightingGfi;
		//lightingGfi.buffer = lightingPass->getFBO();
		//lightingGfi.texturePos.push_back(0);
		//lightingGfi.bindPos.push_back(0);
		//lightingGfi.isDepth.push_back(false);
		//
		//finalPass->addFBOInput(lightingGfi);
		//
		//_bh->addBatch(lightingPass, "Final Pass", 20);
	}

	SDL_Event event;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0.0f;

	bool quit = false;

	_initialize();

	while( !quit ) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;

			_eh->keyboardInput(event);
			switch (event.key.keysym.sym) {
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
				if (c.counter >= 1.f) {
					c.enableMouse = !c.enableMouse;
					SDL_ShowCursor(c.enableMouse);
					c.counter = 0.f;
				}
				break;
			default:
				break;
			}

			switch (event.type) {
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_LSHIFT)
					c.pressedShift = false;
				if (event.key.keysym.sym == SDLK_SPACE)
					c.moveUp = false;
				if (event.key.keysym.sym == SDLK_LCTRL)
					c.moveDown = false;
				if (event.key.keysym.sym == SDLK_w)
					c.moveForward = false;
				if (event.key.keysym.sym == SDLK_a)
					c.moveLeft = false;
				if (event.key.keysym.sym == SDLK_s)
					c.moveBack = false;
				if (event.key.keysym.sym == SDLK_d)
					c.moveRight = false;
				break;
			default:
				break;
			}

		}
		_eh->addNewEntities();
		_eh->update(deltaTime);

		c.getView();
		c.update(deltaTime, 1, _window);
		//b->render(_window);
		//lightingPass->render(_window);
		_bh->render(_window);

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;

		


		SDL_GL_SwapWindow(_window->getWindow());
	}

	//TEST
}