#pragma once
#include "entity.hpp"
#include "component.hpp"

class GameController : public Component {
private:
	Entity* _player;
public:
	GameController();
	~GameController();
	void initialize();
	void update(double dt);
};