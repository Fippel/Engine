#include "statehandler.hpp"

StateHandler* StateHandler::_instance = 0;

StateHandler::StateHandler() {
	_currstate = nullptr;
}

StateHandler::~StateHandler() {
	
}

StateHandler * StateHandler::getInstance() {
	if (!_instance)
		_instance = new StateHandler();

	return _instance;
}

State * StateHandler::getState() {
	return _currstate;
}

void StateHandler::newState(State * state) {
	if (_currstate) {
		_currstate->destroy();
		delete _currstate;

	}
	_currstate = state;
	_currstate->initialize();

}

void StateHandler::killState() {
	if (_currstate) {
		_currstate->destroy();
		delete _currstate;
	}
	_currstate = nullptr;
}
