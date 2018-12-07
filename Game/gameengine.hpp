#pragma once
#include "batchhandler.hpp"
#include "entityhandler.hpp"
#include "fileloader.hpp"


#include "textdata.hpp"

class GameEngine {
private:
	Window* _window;
//----------------------------------
	BatchHandler* _bh;
	EntityHandler* _eh;
	FileLoader* _fl;

	freetype ft;

	void _initialize();
public:
	GameEngine();
	~GameEngine();

	void run();
};