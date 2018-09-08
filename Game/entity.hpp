#pragma once
#include <string>
#include "batchhandler.hpp"
#include "component.hpp"
#include "fileloader.hpp"

class EntityHandler;

class Entity {
private:
	std::string _name;
	unsigned int _index;
	EntityHandler* _eh;
	BatchHandler* _bh;
	FileLoader* _fl;
	bool _isDead = false;
	//Network* n;
	//--------------------

	std::vector<Component*> _comps;
public:
	Entity(std::string name);
	~Entity();
	bool dead();
	void kill();
	void setup(unsigned int index, EntityHandler* eh, BatchHandler* bh, FileLoader* fl);
	std::string getName();
	EntityHandler* getEH();
	BatchHandler* getBH();
	FileLoader* Entity::getFL();
	//--------------------

	void addComponent(Component* comp);
	void removeComponent(std::string name);
	Component* getComponent(std::string name);

	void update(double dt);
};