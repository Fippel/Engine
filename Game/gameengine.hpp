#pragma once
#include "batchhandler.hpp"

class GameEngine {
private:
	Window* _window;
//----------------------------------
	BatchHandler* _bh;
public:
	GameEngine();
	~GameEngine();

	void run();
};