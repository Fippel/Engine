#include "camera.hpp"
#include "window.hpp"
#include "engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

void Camera::update(float dt, float y) {
	if (!enableMouse) {
		glm::ivec2 prev = mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		if (prev != mousePos) {
			auto sizes = Engine::getInstance()->getWindow()->getSizes();
			mousePos -= sizes / 2;

			pitch += prev.y * 0.001f;
			yaw -= prev.x * 0.001f;
			float hpi = glm::half_pi<float>() - 0.001;
			pitch = glm::clamp(pitch, -hpi, hpi);
			SDL_WarpMouseInWindow(Engine::getInstance()->getWindow()->getWindow(), sizes.x / 2, sizes.y / 2);
		}
	}
	float speed = 350.f;
	if (pressedShift)
		speed *= 30;

	glm::vec3 walkDir;
	if (moveForward)
		walkDir += glm::vec3(0, 0, 1);
	if (moveBack)
		walkDir += glm::vec3(0, 0, -1);
	if (moveLeft)
		walkDir += glm::vec3(1, 0, 0);
	if (moveRight)
		walkDir += glm::vec3(-1, 0, 0);

	orientation = glm::quat(glm::vec3(0, yaw, 0)) * glm::quat(glm::vec3(pitch, 0, 0));
	
	walkDir = orientation * walkDir;

	position += walkDir * dt * speed * 0.001f;
	//position.y = y;
	if (moveUp)
		position.y += speed * dt;
	if (moveDown)
		position.y -= speed * dt;

	counter += 1 * dt;
}

glm::mat4* Camera::getView() {
	view = glm::inverse(glm::translate(position) * glm::mat4_cast(glm::rotate(orientation, glm::pi<float>(), glm::vec3(0, 1, 0))));
	return &view;
}

glm::mat4* Camera::getProj() {
	auto size = Engine::getInstance()->getWindow()->getSizes();
	float aspect = size.x / (float)size.y;

	proj = glm::perspective(glm::radians(70.f), aspect, zNear, zFar);
	return &proj;
}