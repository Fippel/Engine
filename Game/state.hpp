#pragma once

#include "batchhandler.hpp"
#include "entityhandler.hpp"
#define StateType unsigned int

enum {
	MENU_STATE
};

class State {
protected:
	StateType type;
public:
	State();
	virtual ~State();

	StateType getType();
	virtual void initialize();
	virtual void update(double dt);
	virtual void destroy();
};
