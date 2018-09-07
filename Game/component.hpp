#pragma once

#include <string>

class Component {
private:
	std::string _name = "NULL";
	bool _isDead = false;
public:
	Component();
	virtual ~Component();
	bool dead();
	void kill();
	std::string getName();

	virtual void initialize() = 0;
	virtual void update(float dt) = 0;
};