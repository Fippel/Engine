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
	MeshComponent* mc = new MeshComponent();
	_parent->addComponent(mc);
	mc->loadModel("assets/models/ARENA_unfished.obj");

	Entity* testbro = new Entity("Test");
	mc = new MeshComponent();
	_parent->getEH()->add(testbro);
	testbro->addComponent(mc);
	mc->loadModel("assets/models/bunny.obj");
	
}

void GameController::update(double dt) {
	//printf("%f\n", 1.0f / dt);
}
