﻿#pragma once
#include "Camera.h"
#include "Sun.h"
#include "Cottage.h"

class Scene
{
public:
	Scene(float s)
		: m_camera(10.0f, 5.0f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
		, m_sun(s / 2, s / 2, s * 0.7, 0.5f, 0.992f, 0.866f, 0.376f)
		, m_cottage(m_size / 8, m_size / 8, 0, 4)
	{
		m_size = s;
	}
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

	void LoadingTexture(const char* name, unsigned int& index);
	void HandlingMovement(GLFWwindow* window);	
	
	void DrawLand();
	void Draw();

	float GetSize();
	Cottage* GetCottage();

	glm::dvec3 GetCameraPos();
	glm::dvec3 GetCameraFront();
	glm::dvec3 GetCameraUp();

private:
	float m_size;
	float theta = 0.0f;
	Camera m_camera;

	Sun m_sun;
	Cottage m_cottage;
};