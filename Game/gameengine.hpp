#pragma once
#include "batchhandler.hpp"
#include "entityhandler.hpp"
#include "fileloader.hpp"
#include "client.hpp"


#include "textdata.hpp"

class GameEngine {
private:
	Window* _window;
//----------------------------------
	BatchHandler* _bh;
	EntityHandler* _eh;
	FileLoader* _fl;

	Client _client;
	freetype* ft;

	void _initialize();
public:
	GameEngine();
	~GameEngine();

	void run();
};