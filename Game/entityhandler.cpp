#include "entityhandler.hpp"

EntityHandler::EntityHandler() {
	this->currentIndex = 0;
}

EntityHandler::~EntityHandler() {
	
}

unsigned int EntityHandler::add(Entity* ent) {
	_entities[currentIndex] = ent;
	ent->setup(currentIndex++, this, _bh);
	return 0;
}

void EntityHandler::remove(unsigned int index) {
	_entities.erase(index);
}

std::vector<Entity*> EntityHandler::getEntity(std::string name) {

	std::vector<Entity*> vec;
	for (std::map<unsigned int, Entity*>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
		if (it->second->getName()==name)
			vec.push_back(it->second);
	}

	return vec;
}

Entity* EntityHandler::getEntity(unsigned int index) {
	return _entities[index];
}
