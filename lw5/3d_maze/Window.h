#pragma once
#include <stdexcept>
#include "Cube.h"
#include "Camera.h"
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
class Window
{
public:
	Window(int w, int h, const char* title)
		: m_window{ MakeWindow(w, h, title) }
		, m_cube()
		, m_camera(22.0f, 10.0f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}

		m_cube.SetSideColor(CubeSide::NEGATIVE_X, 255, 0, 0);
		m_cube.SetSideColor(CubeSide::POSITIVE_X, 0, 255, 0);
		m_cube.SetSideColor(CubeSide::NEGATIVE_Y, 0, 0, 255);
		m_cube.SetSideColor(CubeSide::POSITIVE_Y, 255, 255, 0);
		m_cube.SetSideColor(CubeSide::NEGATIVE_Z, 0, 255, 255);
		m_cube.SetSideColor(CubeSide::POSITIVE_Z, 255, 0, 255);
	}
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	virtual ~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Run();

private:
	
	const static int mazeSize = 20;

	void OnRunStart();

	void Draw(GLFWwindow* window, Cube m_cube, int width, int height);

	static void SetupProjectionMatrix(int width, int height);

	void SetupCameraMatrix(glm::dvec3 cameraPos, glm::dvec3 cameraFront, glm::dvec3 cameraUp);

	void ReadMazeFromFile(int(&maze)[mazeSize][mazeSize]);

	static GLFWwindow* MakeWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
	Cube m_cube;
	Camera m_camera;
};