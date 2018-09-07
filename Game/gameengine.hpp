#pragma once
#include "batchhandler.hpp"
#include "entityhandler.hpp"

class GameEngine {
private:
	Window* _window;
//----------------------------------
	BatchHandler* _bh;
	EntityHandler* _eh;
public:
	GameEngine();
	~GameEngine();

	void run();
};