#pragma once
#include "entity.hpp"

class PlayerComponent : Component {
private:
public:
	PlayerComponent();
	~PlayerComponent();
	void update(double dt);
};