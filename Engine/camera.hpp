#pragma once


#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Window;
class Camera {
private:

public:
	glm::ivec2 mousePos = { 0, 0 };
	glm::vec3 position = { 0, 0, 0 };
	glm::quat orientation;
	glm::mat4 view;
	glm::mat4 proj;

	bool pressedShift = false;
	bool moveUp = false;
	bool moveDown = false;
	bool moveForward = false;
	bool moveBack = false;
	bool moveRight = false;
	bool moveLeft = false;
	bool enableMouse = true;

	float zNear = 0.1f;
	float zFar = 100.f;
	float pitch;
	float yaw;
	float counter = 0.f;

	glm::mat4* Camera::getView();
	
	void update(float dt, float y, Window* w);

	glm::mat4* Camera::getProj(glm::ivec2 size);
};