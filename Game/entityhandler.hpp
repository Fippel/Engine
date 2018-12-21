#pragma once
#include "entity.hpp"
#include <vector>
#include <map>
#include "fileloader.hpp"

class EntityHandler {
private:
	std::map<unsigned int, Entity*> _entities;
	std::map<unsigned int, Entity*> _newEntities;

	bool _clean = false;
	int currentNewIndex;
	int currentIndex;

	static EntityHandler* _instance;
	EntityHandler();
	void _realClean();
public:
	~EntityHandler();

	static EntityHandler* getInstance();

	unsigned int add(Entity* ent);
	void remove(unsigned int index);
	std::vector<Entity*> getEntity(std::string name);
	Entity* getEntity(unsigned int index);
	void addNewEntities();
	void clean();

	void keyboardInput(SDL_Event key);
	void update(double dt);
};