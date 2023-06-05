#define _USE_MATH_DEFINES
#include "glfw3.h"
#include "Window.h"
#include <chrono>
#include <cmath>

GLFWwindow* Window::MakeWindow(int w, int h, const char* title)
{
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	return glfwCreateWindow(w, h, title, nullptr, nullptr);
}

void Window::Run()
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
}

void Window::OnRunStart()
{
	// Включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// Задаем цвет заливки фона
	glClearColor(1, 1, 1, 1);
}

void Window::Draw(int width, int height)
{
	// Предварительная очиствка кадра
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Переопределение матрицы проецирования
	SetupProjectionMatrix(width, height);


	// Отрисовка флага
	m_flag.Draw();

}

void Window::SetupProjectionMatrix(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double aspectRatio = double(width) / double(height);
	double viewWidth = 2.0;
	double viewHeight = viewWidth;
	if (aspectRatio > 1.0)
	{
		viewWidth = viewHeight * aspectRatio;
	}
	else
	{
		viewHeight = viewWidth / aspectRatio;
	}
	glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
}

