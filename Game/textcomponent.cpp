#include "textcomponent.hpp"
#include "batchhandler.hpp"
#include "textdata.hpp"

TextComponent::TextComponent() {
	this->_name = "TextComponent";
	this->_pos = glm::vec2(150, 150);
	_scale = 1.0f;
	_model = nullptr;
}

TextComponent::~TextComponent() {
	if (this->_model)
		delete this->_model;
}

void TextComponent::initialize() {
}

void TextComponent::update(double dt) {
}

void TextComponent::keyPress(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {

		SDL_Keycode key = event.key.keysym.sym;
		std::string tmp = _text;

		if (key == SDLK_a)
			tmp += "a";
		if (key == SDLK_n)
			tmp += "n";
		if (key == SDLK_l)
			tmp += "l";
		if (key == SDLK_d)
			tmp += "d";
		if (key == SDLK_s)
			tmp += "s";
		if (key == SDLK_i)
			tmp += "i";

		if (tmp != _text) {
			_text = tmp;
			if (_model) {
				BatchHandler::getInstance()->getBatch("Text Pass")->removeModel(_model);
				delete _model;
			}

			_model = new Model(freetype::getInstance()->generateText(_text, _pos.x, _pos.y, _scale, glm::vec3(1, 1, 1)));
			BatchHandler::getInstance()->getBatch("Text Pass")->registerModel(_model);
		}
	}
}
