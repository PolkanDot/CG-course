#pragma once
#include <stdexcept>
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
#include "CCanvas.h"
#include "CProgram.h"

class CWindow
{
public:
	CWindow(int w, int h, const char* title)
		: m_window{ MakeWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create CWindow");
		}
	}

	virtual ~CWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run();

private:

	void OnRunStart();
	void InitShaders();

	void Draw(int width, int height);

	static void SetupProjectionMatrix(int width, int height);

	static GLFWwindow* MakeWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
	CCanvas m_canvas;
	CProgram m_program;
};