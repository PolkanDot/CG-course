#pragma once
#include "Camera.h"

class Scene
{
public:
	Scene(float w, float l)
		:m_camera(0.0f, 8.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f)
	{
		m_width = w;
		m_length = l;
	}
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

	void HandlingMovement(GLFWwindow* window);

	void Draw();

	float GetWidth();
	float GetLength();

	glm::dvec3 GetCameraPos();
	glm::dvec3 GetCameraFront();
	glm::dvec3 GetCameraUp();

private:
	float m_width;
	float m_length;
	Camera m_camera;
};