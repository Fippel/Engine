#pragma once
#include "batchhandler.hpp"
#include "entityhandler.hpp"
#include "fileloader.hpp"
#include "client.hpp"

class GameEngine {
private:
	Window* _window;
//----------------------------------
	BatchHandler* _bh;
	EntityHandler* _eh;
	FileLoader* _fl;

	Client _client;

	void _initialize();
public:
	GameEngine();
	~GameEngine();

	void run();
};