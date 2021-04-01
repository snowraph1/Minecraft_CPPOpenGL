#include "Camera.h"

#include <iostream>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

Camera::Camera(float ffov, float fnearPlane, float ffarPlane, int fframeBufferWidth, int fframeBufferHeight, glm::vec3 finitialPos, glm::vec3 finitialViewDirection)
{
	fov = ffov;
	nearPlane = fnearPlane;
	farPlane = ffarPlane;

	frameBufferWidth = fframeBufferWidth;
	frameBufferHeight = fframeBufferHeight;

	position = finitialPos;
	viewDirection = finitialViewDirection;
	worldUp = glm::vec3(0.f, 1.f, 0.f);
}

glm::mat4 Camera::getWorldToViewMatrix() const {
	return glm::lookAt(position, position + viewDirection, worldUp);
}

glm::mat4 Camera::getProjectionMatrix() const {
	return glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);
}

glm::vec3 Camera::getCameraWorldPosition() const {
	return position;
}

void Camera::move(glm::vec3 move) {
	position += move;
}

void Camera::moveTo(glm::vec3 pos) {
	position = pos;
}

void Camera::changeDirection(glm::vec3 dir) {
	viewDirection = dir;
}