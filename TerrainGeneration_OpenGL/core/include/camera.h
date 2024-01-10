#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mymaths.hpp"

class Camera
{
private:
	Camera();
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
public:
	static Camera* GetInstance();

	glm::vec3 GetCameraPos();
	glm::vec3 GetCameraFront();
	glm::vec3 GetCameraUp();

	glm::vec3 SetCameraPos(glm::vec3 _cameraPos);
	glm::vec3 SetCameraFront(glm::vec3 _cameraFront);
	glm::vec3 SetCameraUp(glm::vec3 _cameraUp);
};