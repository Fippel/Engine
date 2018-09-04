#include "gameengine.hpp"
#include "window.hpp"

GameEngine::GameEngine() {
	_bh = new BatchHandler();
	_window = new Window("Meow"); // NAMN PLOX :D
}

GameEngine::~GameEngine() {
	delete _bh;
	delete _window;
}

void GameEngine::run() {




	_bh->render(_window);
}
