#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Camera
{
private:

	mat4 projectionMatrix{ 1.0f };
	mat4 viewMatrix{ 1.0 };

public:

	/*void projectionOrtho(float left, float right, float top, float bottom, float near, float far);
	void perspectiveProjecttion(float fovy, float aspect, float near, float far);

	void viewDirection(vec3 position, vec3 direction, vec3 up = vec3{ 0.0f, -1.0f, 0.0f });
	void viewTarget(vec3 position, vec3 direction, vec3 up = vec3{ 0.0f, -1.0f, 0.0f });
	void setViewXYZ(vec3 position, vec3 rotation);

	const mat4& getProjection() const { return projectionMatrix; }
	const mat4& getView() const { return viewMatrix; }*/

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

	float fov = 45.0f;
	float aspectRatio = width / height;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

};
