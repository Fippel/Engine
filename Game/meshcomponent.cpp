#include "meshcomponent.hpp"
#include "entity.hpp"

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
	
	this->_model = _parent->getFL()->loadModel(filePath.c_str(), true);
	_parent->getBH()->getBatch("TESTBITCH")->registerModel(_model); //TEMPORARY
	_scale = glm::vec3(1,1,1);
	_pos = glm::vec3(0,0,0);
}

void MeshComponent::update(double dt) {
	_pos.x += 0.1 * dt;
	_model->updateModelMatrix(_pos, _scale);
	float fps = 1.0 / dt;
	printf("%f\n", fps);
}
