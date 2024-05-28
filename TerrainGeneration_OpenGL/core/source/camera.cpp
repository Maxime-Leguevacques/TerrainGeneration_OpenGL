#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mymaths.hpp"


Camera* Camera::GetInstance()
{
	Camera* instance = new Camera();
	return instance;
}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		cameraPos += cameraFront * velocity;
	if (direction == BACKWARD)
		cameraPos -= cameraFront * velocity;
	if (direction == LEFT)
		cameraPos -= Right * velocity;
	if (direction == RIGHT)
		cameraPos += Right * velocity;
	if (direction == UP)
		cameraPos.y += velocity;
	if (direction == DOWN)
		cameraPos.y -= velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}