#include "meshcomponent.hpp"
#include "entity.hpp"
#include "entityhandler.hpp"

MeshComponent::MeshComponent() {
	this->_name = "MeshComponent";
	_model = nullptr;
}

MeshComponent::~MeshComponent() {
	if(this->_model)
		delete this->_model;
}

void MeshComponent::initialize() {
}



void MeshComponent::loadModel(std::string filePath) {
	if(this->_model)
		delete this->_model;
	
	_model = FileLoader::getInstance()->loadModel(filePath.c_str(), true);
	BatchHandler::getInstance()->getBatch("TESTBITCH")->registerModel(_model);
	_scale = glm::vec3(1,1,1);
	_pos = glm::vec3(0,0,0);
}

void MeshComponent::update(double dt) {
	//_pos.x += 0.1 * dt;
	_model->updateModelMatrix(_pos, _scale);
	//printf("%f\n", fps);
}

void MeshComponent::keyPress(SDL_Keycode key) {
	if (key == SDLK_SPACE) {
		Entity* ent = new Entity("testnamn");
		MeshComponent* mc = new MeshComponent();
		mc->loadModel("assets/models/ARENA_unfished.obj");
		mc->_pos = glm::vec3(10, 10, 10);
		ent->addComponent(mc);
		EntityHandler::getInstance()->add(ent);
	}
}
