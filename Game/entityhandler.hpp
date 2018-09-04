#pragma once
#include "entity.hpp"
#include <vector>
#include <map>

class EntityHandler {
private:
	std::map<unsigned int, Entity*> _entities;
	int currentIndex;
	BatchHandler* _bh;
public:
	EntityHandler();
	~EntityHandler();

	unsigned int add(Entity* ent);
	void remove(unsigned int index);
	std::vector<Entity*> getEntity(std::string name);
	Entity* getEntity(unsigned int index);
};