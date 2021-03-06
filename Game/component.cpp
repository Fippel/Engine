#include "component.hpp"

Component::Component() { }

Component::~Component() { }

bool Component::dead() {
	return _isDead;
}

void Component::setParent(Entity* parent) {
	this->_parent = parent;
}

void Component::kill() {
	_isDead = true;
}

std::string Component::getName() {
	return _name;
}
