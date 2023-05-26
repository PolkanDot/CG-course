﻿#pragma once
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

	void Draw();

	float GetSize();

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
	float m_size;

	Camera m_camera;
	Cube m_cube;
};