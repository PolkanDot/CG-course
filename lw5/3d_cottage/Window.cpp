#define _USE_MATH_DEFINES
#include "glfw3.h"
#include "Window.h"
#include "Constants.h"
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
	//
	//glEnable(GL_CULL_FACE);
	// 
	//glCullFace(GL_BACK);
	// 
	// 
	//glFrontFace(GL_CCW);

	//
	m_scene.LoadingTexture("textures/sky.png", m_scene.skyTexture);
	m_scene.LoadingTexture("textures/grass.png", m_scene.bottomTexture);
	m_scene.LoadingTexture("textures/1.png", m_scene.wallTexture1);
	m_scene.LoadingTexture("textures/2.png", m_scene.wallTexture2);
	m_scene.LoadingTexture("textures/3.png", m_scene.wallTexture3);
	m_scene.LoadingTexture("textures/4.png", m_scene.wallTexture4);
	// 
	glEnable(GL_DEPTH_TEST);
	// 
	glClearColor(1, 1, 1, 1);
	// 
	glEnable(GL_LIGHTING);
	// 
	glEnable(GL_LIGHT0);
	// 
	glEnable(GL_COLOR_MATERIAL);
	// 
	glEnable(GL_NORMALIZE);
	//
	float backgroundLighting[] = { 1, 1, 1, 0.01 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, backgroundLighting);
}

void Window::Draw(int width, int height)
{
	// Обработка нажатий клавишь
	m_scene.HandlingMovement(m_window);
	// Предварительная очиствка кадра
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Переопределение матрицы проецирования
	SetupProjectionMatrix(width, height);
	// Переопределение видовой матрицы
	SetupCameraMatrix(m_scene.GetCameraPos(), m_scene.GetCameraFront(), m_scene.GetCameraUp());

	// Отрисовка сцены
	m_scene.Draw();

}

void Window::SetupProjectionMatrix(int width, int height)
{
	glViewport(0, 0, width, height);

	// 
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto projMat = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 20.0);
	glLoadMatrixd(&projMat[0][0]);
}

void Window::SetupCameraMatrix(glm::dvec3 cameraPos, glm::dvec3 cameraFront, glm::dvec3 cameraUp)
{
	glMatrixMode(GL_MODELVIEW);
	const auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glLoadMatrixd(&view[0][0]);
}