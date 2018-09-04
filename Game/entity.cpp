#include "entity.hpp"

Entity::Entity(std::string name) {
	_name = name;
}

Entity::~Entity() {
}

void Entity::setup(unsigned int index, EntityHandler* eh, BatchHandler* bh) {
	_index = index;
	_bh = bh;
	_eh = eh;
}

std::string Entity::getName() {
	return _name;
}

EntityHandler* Entity::getEH() {
	return _eh;
}

BatchHandler* Entity::getBH() {
	return _bh;
}
