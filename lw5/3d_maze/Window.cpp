#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include "Window.h"
#include "Constants.h"
#include "Includes/stb_image.h"
#include <chrono>
#include <cmath>
// �������� ��������� ����� �������� �������
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
	// �������� ����� ���������� ������
	glEnable(GL_CULL_FACE);
	// ��������������� ����� ��������� ������� ������
	glCullFace(GL_BACK);
	// ������� ��������� ��������� �������, ���� ��� �� ���������
	// ����� ������ �������������� ������ ������� �������
	glFrontFace(GL_CCW);

	unsigned int texture;

	int width, height, cnt;
	unsigned char* data = stbi_load("01.png", &width, &height, &cnt, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	stbi_image_free(data);
	

	// �������� ���� ������� ��� �������� ��������� ����� � ������������
	glEnable(GL_DEPTH_TEST);
	// ������ ���� ������� ������ �����
	glClearColor(1, 0, 1, 1);
	//������ �������� ������ �� �����
	m_maze.ReadMazeFromFile();

	m_maze.AddFog();
}

void Window::Draw(int width, int height)
{
	double currentFrame = static_cast<double>(glfwGetTime());
	m_camera.m_deltaTime = currentFrame - m_camera.m_lastFrame;
	m_camera.m_lastFrame = currentFrame;

	m_camera.ProcessInput(m_window, m_maze.maze);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 1, 1);

	SetupProjectionMatrix(width, height);
	SetupCameraMatrix(m_camera.m_cameraPos, m_camera.m_cameraFront, m_camera.m_cameraUp);

	//m_maze.Draw();
	glBegin(GL_QUADS);
	{
		//glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		//glTexCoord2f(20, 0);
		glVertex3f(mazeSize, 0, 0);
		//glTexCoord2f(20, 20);
		glVertex3f(mazeSize, mazeSize, 0);
		//glTexCoord2f(0, 20);
		glVertex3f(0, mazeSize, 0);
	}
	glEnd();


	glTranslatef(0, 0, 1);

	glBegin(GL_QUADS);
	{
		//glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		//glTexCoord2f(1, 0);
		glVertex3f(0, mazeSize, 0);
		//glTexCoord2f(1, 1);
		glVertex3f(mazeSize, mazeSize, 0);
		//glTexCoord2f(0, 1);
		glVertex3f(mazeSize, 0, 0);
	}
	glEnd();

	glTranslatef(0, 0, -1);

	//������ ����� ���������

	for (int y = mazeSize - 1; y >= 0; y--)
		for (int x = mazeSize - 1; x >= 0; x--)
		{
			if (m_maze.maze[x][y] == 0)
			{
				m_cube.Draw(x, y);
			}
		}
}

void Window::SetupProjectionMatrix(int width, int height)
{
	glViewport(0, 0, width, height);

	// ��������� ����������� ������ ���������� ������� ����
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

