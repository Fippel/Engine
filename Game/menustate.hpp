#pragma once
#include "state.hpp"

class MenuState : public State {
private:
	
public:
	MenuState();
	~MenuState();

	virtual void initialize();
	virtual void update(double dt);
	virtual void destroy();
};