#pragma once

#include <glm.hpp>

class Camera
{
	float fov;
	float nearPlane;
	float farPlane;

	int frameBufferWidth;
	int frameBufferHeight;

	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 worldUp;

public:
	Camera(float fov, float nearPlane, float farPlane, int frameBufferWidth, int frameBufferHeight, glm::vec3 initialPos, glm::vec3 initialViewDirection);
	
	glm::mat4 getWorldToViewMatrix() const;

	glm::mat4 getProjectionMatrix() const;

	glm::vec3 getCameraWorldPosition() const;

	void move(glm::vec3 move);

	void moveTo(glm::vec3 pos);

	void changeDirection(glm::vec3 dir);
};

