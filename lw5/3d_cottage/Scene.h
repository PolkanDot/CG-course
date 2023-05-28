#pragma once
#include "Camera.h"
#include "Cube.h"

class Scene
{
public:
	Scene(float s)
		: m_camera(10.0f, 5.0f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
		, m_cube()
	{
		m_size = s;
	}
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

	void LoadingTexture(const char* name, unsigned int& index);
	void HandlingMovement(GLFWwindow* window);

	void DrawSun();
	void DrawLand();
	void DrawGarage(float coordX, float coordY, float height);
	void DrawCottage(float coordX, float coordY, float height);
	

	void Draw();

	float GetSize();

	glm::dvec3 GetCameraPos();
	glm::dvec3 GetCameraFront();
	glm::dvec3 GetCameraUp();
	// плохо
	unsigned int cottageBottomTexture = 0;
	unsigned int bottomTexture = 0;
	unsigned int cottageMidleTexture = 0;
	unsigned int wallTexture2 = 0;
	unsigned int wallTexture3 = 0;
	unsigned int wallTexture4 = 0;

private:
	float m_size;
	float theta = 0.0f;
	Camera m_camera;
	Cube m_cube;
};