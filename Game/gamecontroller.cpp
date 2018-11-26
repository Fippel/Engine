#include "gamecontroller.hpp"
#include "meshcomponent.hpp"
#include "EntityHandler.hpp"

GameController::GameController() {
	this->_name = "GameController";
	this->_player = nullptr;
}

GameController::~GameController() {
	if(_player)
		delete _player;
}

void GameController::initialize() {
	_state = new GameState();
	_state->initialize(_parent->getBH(), _parent->getEH());


}

void GameController::update(double dt) {
	//printf("%f\n", 1.0f / dt);
	_state->update(dt);
}
