#pragma once

#include "batchhandler.hpp"
#include "entityhandler.hpp"

class State {
protected:
	BatchHandler* _bh;
	EntityHandler* _eh;
public:
	State();
	virtual ~State();

	virtual void initialize(BatchHandler* bh, EntityHandler* eh);
	virtual void update(double dt);
	virtual void destroy();
};
