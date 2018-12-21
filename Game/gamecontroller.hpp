#pragma once
#include "entity.hpp"
#include "component.hpp"
#include "gamestate.hpp"

class GameController : public Component { // ska detta vara en component? singleton?
private:
	Entity* _player;
	State* _state;
public:
	GameController();
	~GameController();
	void initialize();
	void update(double dt);
};