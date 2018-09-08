#include "gamecontroller.hpp"
#include "meshcomponent.hpp"

GameController::GameController() {
	this->_name = "GameController";
	this->_player = nullptr;
}

GameController::~GameController() {
	if(_player)
		delete _player;
}

void GameController::initialize() {
	MeshComponent* mc = new MeshComponent();
	_parent->addComponent(mc);
	mc->loadModel("assets/models/sponza.obj");
}

void GameController::update(double dt) {
}
