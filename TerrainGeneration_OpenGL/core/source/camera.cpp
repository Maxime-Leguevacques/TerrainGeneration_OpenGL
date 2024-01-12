#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mymaths.hpp"

Camera::Camera()
	:cameraPos(glm::vec3(0.0f, 0.0f, 0.3f)), 
	cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
	cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Camera* Camera::GetInstance()
{
	Camera* instance = new Camera();
	return instance;
}

glm::vec3 Camera::GetCameraPos()
{
	return cameraPos;
}

glm::vec3 Camera::GetCameraFront()
{
	return cameraFront;
}

glm::vec3 Camera::GetCameraUp()
{
	return cameraUp;
}
