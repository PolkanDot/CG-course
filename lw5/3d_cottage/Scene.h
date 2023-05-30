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

	void DrawCircle(float cx, float cy, float r, int num_segments);
	void DrawSun();
	void DrawLand();
	void DrawRoof(float length, float width);
	void DrawMainHouse(float coordX, float coordY, float length, float width, float height);
	void DrawGarageDoor(float coordX, float coordY, float width, float height);
	void DrawGarageRoof(float coordX, float coordY, float coordZ, float length, float width, float height);
	void DrawGarage(float coordX, float coordY, float length, float width, float height);
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
	unsigned int roofTop = 0;
	unsigned int garageRoofBottom = 0;
	unsigned int garageDoor = 0;
	unsigned int mainHouseBottom = 0;
	unsigned int m = 0;

private:
	float m_size;
	float theta = 0.0f;
	Camera m_camera;
	Cube m_cube;
};