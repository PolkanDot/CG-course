﻿#define _USE_MATH_DEFINES
#include "glfw3.h"
#include <chrono>
#include <cmath>
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
#include <stdexcept>

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ MakeWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);
		OnRunStart();
		while (!glfwWindowShouldClose(m_window))
		{
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(w, h);
			glFinish();
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		OnRunEnd();
	}

private:
	virtual void Draw(int width, int height) = 0;

	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title)
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
	GLFWwindow* m_window;
};

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void OnRunStart() override
	{
		// Задаем цвет очистки буфера кадра
		glClearColor(1, 1, 0, 1);
	}

	void Draw(int width, int height) override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SetupProjectionMatrix(width, height);
		SetupCameraMatrix();
		glEnable(GL_DEPTH_TEST);

		// Рисуем красный квадрат в плоскости XOY
		glColor3f(1, 0, 0);
		glRectf(-1, -1, 1, 1);

		// Рисуем синий квадрат в плоскости Z=0, предварительно задав для него
		// трансформацию повоота вокруг оси Y и а затем переноса на 0.2 вдоль оси Z
		// Порядок умножения матриц - обратный
		glTranslatef(0, 0, 0.2f);
		glRotatef(60, 0, 1, 0);

		glColor3f(0, 0, 1);
		glRectf(-0.5, -1.0, +0.5, +0.5);
	}

	static void SetupProjectionMatrix(int width, int height)
	{
		glViewport(0, 0, width, height);

		// Вычисляем соотношение сторон клиентской области окна
		double aspect = double(width) / double(height);

		glMatrixMode(GL_PROJECTION);
		const auto projMat = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 10.0);
		glLoadMatrixd(&projMat[0][0]);
	}

	static void SetupCameraMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		const auto lookAtMat = glm::lookAt(
			glm::dvec3(0, -4, 4), // Положение камеры
			glm::dvec3(0, 0, 0), // Точка, в которую направлена камера
			glm::dvec3(0, 1, 0) // Направление "вверх"
		);
		glLoadMatrixd(&lookAtMat[0][0]);
	}
};

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 800, 600, "Two rectangles" };
	window.Run();
}