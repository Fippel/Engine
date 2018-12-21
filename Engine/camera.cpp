#include "camera.hpp"
#include "engine.hpp"
#include "window.hpp"

Camera* Camera::_instance = 0;

void Camera::update(float dt, float y, Window* w) {
	if (!enableMouse) {
		glm::ivec2 prev = mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		if (prev != mousePos) {
			glm::ivec2 sizes = w->getSizes();
			mousePos -= sizes / 2;
	
			pitch += prev.y * 0.001f;
			yaw -= prev.x * 0.001f;
			float hpi = glm::half_pi<float>() - 0.001;
			pitch = glm::clamp(pitch, -hpi, hpi);
			//yaw = glm::clamp(yaw, -1.0f, 1.0f);
			SDL_WarpMouseInWindow(w->getWindow(), sizes.x / 2, sizes.y / 2);
		}
	}
	float speed = 500.f;
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

glm::mat4* Camera::getProj(glm::ivec2 size) {
	float aspect = size.x / (float)size.y;

	proj = glm::perspective(glm::radians(70.f), aspect, zNear, zFar);
	return &proj;
}

Camera::Camera() {

}

Camera* Camera::getInstance() {
	if (!_instance)
		_instance = new Camera();
	return _instance;
}

Camera::~Camera() {
}

glm::mat4* Camera::getView() {
	view = glm::inverse(glm::translate(position) * glm::mat4_cast(glm::rotate(orientation, glm::pi<float>(), glm::vec3(0, 1, 0))));
	return &view;
}
