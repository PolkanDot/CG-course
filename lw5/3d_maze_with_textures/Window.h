#pragma once
#include <stdexcept>
#include "Constants.h"
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
#include "Camera.h"
#include "Maze.h"

class Window
{
public:
	Window(int w, int h, const char* title)
		: m_window{ MakeWindow(w, h, title) }
		, m_camera(22.0f, 10.0f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	virtual ~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Run();

private:

	void OnRunStart();

	void Draw(int width, int height);

	static void SetupProjectionMatrix(int width, int height);

	void SetupCameraMatrix(glm::dvec3 cameraPos, glm::dvec3 cameraFront, glm::dvec3 cameraUp);

	static GLFWwindow* MakeWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
	Camera m_camera;
	Maze m_maze;
};