#pragma once
#include "Camera.h"
#include "Cube.h"

class Scene
{
public:
	Scene(float w, float l)
		: m_camera(0.0f, 8.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f)
		, m_cube()
	{
		m_width = w;
		m_length = l;
	}
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

	void LoadingTexture(const char* name, unsigned int& index);
	void HandlingMovement(GLFWwindow* window);

	void Draw();

	float GetWidth();
	float GetLength();

	glm::dvec3 GetCameraPos();
	glm::dvec3 GetCameraFront();
	glm::dvec3 GetCameraUp();
	// плохо
	unsigned int skyTexture = 0;
	unsigned int bottomTexture = 0;
	unsigned int wallTexture1 = 0;
	unsigned int wallTexture2 = 0;
	unsigned int wallTexture3 = 0;
	unsigned int wallTexture4 = 0;

private:
	float m_width;
	float m_length;

	

	Camera m_camera;
	Cube m_cube;
};