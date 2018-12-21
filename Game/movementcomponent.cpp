#include "movementcomponent.hpp"
#include "camera.hpp"

MovementComponent::MovementComponent() {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::initialize() {

}

void MovementComponent::keyPress(SDL_Event event) {
	Camera* c = Camera::getInstance();

	switch (event.key.keysym.sym) {
	case SDLK_LSHIFT:
		c->pressedShift = true;
		break;
	case SDLK_SPACE:
		c->moveUp = true;
		break;
	case SDLK_w:
		c->moveForward = true;
		break;
	case SDLK_a:
		c->moveLeft = true;
		break;
	case SDLK_s:
		c->moveBack = true;
		break;
	case SDLK_d:
		c->moveRight = true;
		break;
	case SDLK_LALT:
		if (c->counter >= 1.f) {
			c->enableMouse = !c->enableMouse;
			SDL_ShowCursor(c->enableMouse);
			c->counter = 0.f;
		}
		break;
	default:
		break;
	}

	switch (event.type) {
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_LSHIFT)
			c->pressedShift = false;
		if (event.key.keysym.sym == SDLK_SPACE)
			c->moveUp = false;
		if (event.key.keysym.sym == SDLK_LCTRL)
			c->moveDown = false;
		if (event.key.keysym.sym == SDLK_w)
			c->moveForward = false;
		if (event.key.keysym.sym == SDLK_a)
			c->moveLeft = false;
		if (event.key.keysym.sym == SDLK_s)
			c->moveBack = false;
		if (event.key.keysym.sym == SDLK_d)
			c->moveRight = false;
		break;
	default:
		break;
	}
}

void MovementComponent::update(double dt) {

}
