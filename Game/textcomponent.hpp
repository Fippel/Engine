#pragma once

#include "component.hpp"
#include "mesh.hpp"

class TextComponent : public Component {
private:
	Model* _model;
	glm::vec2 _pos;
	float _scale;
	std::string _text = "";

public:
	TextComponent();
	~TextComponent();
	void initialize();
	void update(double dt);
	void keyPress(SDL_Event key);
};