#pragma once

#include <string>

class Entity;

class Component {
protected:
	std::string _name = "NULL";
	Entity* _parent;
private:
	bool _isDead = false;
public:
	Component();
	virtual ~Component();
	bool dead();
	void kill();
	std::string getName();

	void setParent(Entity* parent);
	virtual void initialize() = 0;
	virtual void update(double dt) = 0;
};