#pragma once

#include "component.hpp"
#include "mesh.hpp"

class MeshComponent : public Component {
private:
	Model* _model;
	glm::vec3 _pos;
	glm::vec3 _scale;
public:
	MeshComponent();
	~MeshComponent();
	void initialize();
	void loadModel(std::string filePath);
	void update(double dt);
};