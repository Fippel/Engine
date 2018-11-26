#pragma once

#include "state.hpp"

class GameState : public State {
private:

public:
	GameState();
	~GameState();

	void initialize(BatchHandler* bh, EntityHandler* eh);
	void update(double dt);
	void destroy();
};
