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
	bool _isDead = false;
	//Network* n;
	//--------------------

	std::vector<Component*> _comps;
public:
	Entity(std::string name);
	~Entity();
	bool dead();
	void kill();
	void setup(unsigned int index);
	std::string getName();
	//--------------------

	void addComponent(Component* comp);
	void removeComponent(std::string name);
	Component* getComponent(std::string name);

	void keyPress(SDL_Keycode key);
	void update(double dt);
};