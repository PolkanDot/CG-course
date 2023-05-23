#define _USE_MATH_DEFINES
#include "glfw3.h"
#include "Window.h"
#include "Constants.h"
#include <chrono>
#include <cmath>
// устранить мельчешение текстур (фильтрация текстур)
// проблема с архитектурой (все данные в классах публичные, хотябы ... или ... с митмапами) 
// учитывать время между кадрами при поворотах и передвижении, иначе будет ускорятся и замедляться
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
	// Включаем режим отбраковки граней
	//glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	//glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	//glFrontFace(GL_CCW);

	// Загружаем все текстуры
	/*m_maze.LoadingTexture("textures/sky.png", m_maze.skyTexture);
	m_maze.LoadingTexture("textures/grass.png", m_maze.bottomTexture);
	m_maze.LoadingTexture("textures/1.png", m_maze.wallTexture1);
	m_maze.LoadingTexture("textures/2.png", m_maze.wallTexture2);
	m_maze.LoadingTexture("textures/3.png", m_maze.wallTexture3);
	m_maze.LoadingTexture("textures/4.png", m_maze.wallTexture4);*/

	//glEnable(GL_TEXTURE_2D);
	

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);
	// Задаем цвет очистки буфера кадра
	glClearColor(0, 0, 0, 1);
	//Читаем заданный массив их файла
	//m_maze.ReadMazeFromFile();

	//m_maze.AddFog();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

void Window::Draw(int width, int height)
{
	double currentFrame = static_cast<double>(glfwGetTime());
	m_camera.m_deltaTime = currentFrame - m_camera.m_lastFrame;
	m_camera.m_lastFrame = currentFrame;

	glNormal3f(0, 0, 1);
	

	m_camera.ProcessInput(m_window);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	SetupProjectionMatrix(width, height);
	SetupCameraMatrix(m_camera.m_cameraPos, m_camera.m_cameraFront, m_camera.m_cameraUp);


	glPushMatrix();
		// Перемещение источника света
		glRotatef(theta, 0, 1, 0);
		float position[] = { 0, 0, 1, 0 };
		theta += 0.1f;
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		// Отрисовка источника света
		glTranslatef(0, 0, 1);
		glScalef(0.2, 0.2, 0.2);
		glColor3f(1, 1, 1);
		m_scene.Draw();
	glPopMatrix();

	// Рисуем верхний квадрат
	glColor3f(0.3, 0.3, 0.3);
	m_scene.Draw();

}

void Window::SetupProjectionMatrix(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
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

