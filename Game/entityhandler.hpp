#pragma once
#include "entity.hpp"
#include <vector>
#include <map>
#include "fileloader.hpp"

class EntityHandler {
private:
	std::map<unsigned int, Entity*> _entities;
	int currentIndex;
	BatchHandler* _bh;
	FileLoader* _fl;
public:
	EntityHandler(BatchHandler* bh, FileLoader* fl);
	~EntityHandler();

	unsigned int add(Entity* ent);
	void remove(unsigned int index);
	std::vector<Entity*> getEntity(std::string name);
	Entity* getEntity(unsigned int index);

	void update(double dt);
};