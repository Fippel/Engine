#pragma once

#include "batchhandler.hpp"
#include "entityhandler.hpp"

class State {
protected:
public:
	State();
	virtual ~State();

	virtual void initialize();
	virtual void update(double dt);
	virtual void destroy();
};
