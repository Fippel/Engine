#include "gamestate.hpp"
#include "meshcomponent.hpp"

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::initialize() {

	Entity* testbro = new Entity("Test");
	MeshComponent* mc = new MeshComponent();
	EntityHandler::getInstance()->add(testbro);
	testbro->addComponent(mc);
	mc->loadModel("assets/models/ARENA_unfished.obj");
}

void GameState::update(double dt) {
	
}

void GameState::destroy() {
}
