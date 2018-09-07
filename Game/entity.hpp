#pragma once
#include <string>
#include "batchhandler.hpp"
#include "component.hpp"

class EntityHandler;

class Entity {
private:
	std::string _name;
	unsigned int _index;
	EntityHandler* _eh;
	BatchHandler* _bh;
	bool _isDead = false;
	//Network* n;
	//--------------------

	std::vector<Component*> _comps;
public:
	Entity(std::string name);
	~Entity();
	bool dead();
	void kill();
	void setup(unsigned int index, EntityHandler* eh, BatchHandler* bh);
	std::string getName();
	EntityHandler* getEH();
	BatchHandler* getBH();

	//--------------------

	void addComponent(Component* comp);
	void removeComponent(std::string name);
	Component* getComponent(std::string name);
};