#include "entityhandler.hpp"

EntityHandler* EntityHandler::_instance = 0;

EntityHandler::EntityHandler() {
	currentIndex = 0;
	currentNewIndex = 0;
}

EntityHandler::~EntityHandler() {
}

EntityHandler * EntityHandler::getInstance() {
	if (!_instance)
		_instance = new EntityHandler();
	return _instance;
}

unsigned int EntityHandler::add(Entity* ent) {
	_newEntities[currentNewIndex++] = ent;
	//ent->setup(currentNewIndex++);
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

void EntityHandler::addNewEntities() {
	for (std::map<unsigned int, Entity*>::iterator it = _newEntities.begin(); it != _newEntities.end(); ++it) {
		_entities[currentIndex] = it->second;
		it->second->setup(currentIndex++);
	}
	_newEntities.clear();
}

void EntityHandler::keyboardInput(SDL_Keycode key) {

	for (std::map<unsigned int, Entity*>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
		it->second->keyPress(key);
	}
}

void EntityHandler::update(double dt) {
	for(std::map<unsigned int, Entity*>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
		it->second->update(dt);
	}
}
