#include "gamestate.hpp"
#include "meshcomponent.hpp"

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::initialize(BatchHandler * bh, EntityHandler * eh) {
	_bh = bh;
	_eh = eh;

	Entity* testbro = new Entity("Test");
	MeshComponent* mc = new MeshComponent();
	_eh->add(testbro);
	testbro->addComponent(mc);
	mc->loadModel("assets/models/ARENA_unfished.obj");
}

void GameState::update(double dt) {
	
}

void GameState::destroy() {
}
