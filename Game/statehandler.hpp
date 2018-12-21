#pragma once
#include "state.hpp"

class StateHandler {
private:
	static StateHandler* _instance;
	StateHandler();
	
	State* _currstate;

public:
	~StateHandler();
	static StateHandler* getInstance();
	State* getState();
	void newState(State* state);
	void killState();
};