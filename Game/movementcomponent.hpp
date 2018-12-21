#pragma once

#include "component.hpp"

class MovementComponent : public Component { // component for debugging
private:

public:
	MovementComponent();
	~MovementComponent();
	void initialize();
	void keyPress(SDL_Event event);
	void update(double dt);
};
