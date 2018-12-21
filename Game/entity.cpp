#include "entity.hpp"

Entity::Entity(std::string name) {
	_name = name;
}

Entity::~Entity() {
	for (int i = 0; i < _comps.size(); i++) {
		delete _comps[i];
	}
}

bool Entity::dead() {
	return _isDead;
}

void Entity::kill() {
	_isDead = true;
}

void Entity::setup(unsigned int index) {
	_index = index;
}

std::string Entity::getName() {
	return _name;
}

void Entity::addComponent(Component* comp) {
	comp->setParent(this);
	comp->initialize();
	_comps.push_back(comp);
}

void Entity::removeComponent(std::string name) {
	for (int i = 0; i < _comps.size(); i++) {
		if (_comps[i]->getName() == name) {
			delete _comps[i];
			_comps[i] = _comps[_comps.size()-1];
			_comps.pop_back();
		}
	}
}

Component* Entity::getComponent(std::string name) {
	for (int i = 0; i<_comps.size(); i++) {
		if (_comps[i]->getName()==name)
			return _comps[i];
	}
	return nullptr;
}

void Entity::keyPress(SDL_Event event) {
	for (int i = 0; i < this->_comps.size(); i++) {
		_comps[i]->keyPress(event);
	}
}

void Entity::update(double dt) {
	for(int i = 0; i < this->_comps.size(); i++) {
		_comps[i]->update(dt);
	}
}
