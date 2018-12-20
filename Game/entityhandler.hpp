#pragma once
#include "entity.hpp"
#include <vector>
#include <map>
#include "fileloader.hpp"

class EntityHandler {
private:
	std::map<unsigned int, Entity*> _entities;
	std::map<unsigned int, Entity*> _newEntities;

	int currentNewIndex;
	int currentIndex;

	static EntityHandler* _instance;
	EntityHandler();
public:
	~EntityHandler();

	static EntityHandler* getInstance();

	unsigned int add(Entity* ent);
	void remove(unsigned int index);
	std::vector<Entity*> getEntity(std::string name);
	Entity* getEntity(unsigned int index);
	void addNewEntities();

	void keyboardInput(SDL_Event key);
	void update(double dt);
};