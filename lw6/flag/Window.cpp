#define _USE_MATH_DEFINES
#define GLEW_STATIC
#include "glew.h"
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
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}
	if (!GLEW_ARB_shader_objects)
	{
		throw std::runtime_error("Failed to initialize GLEW_ARB_shader_objects");
	}
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
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 0, 10);
	glMatrixMode(GL_MODELVIEW);
}

