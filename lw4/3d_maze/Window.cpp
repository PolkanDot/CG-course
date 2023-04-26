#include "Window.h"

GLFWwindow* Window::MakeWindow(int w, int h, const char* title)
{
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	return glfwCreateWindow(w, h, title, nullptr, nullptr);
}

void Window::Run()
{
	glfwMakeContextCurrent(m_window);
	//glfwSetCursorPosCallback(m_window, static_cast<GLFWcursorposfun*>(mouse_callback(m_window, lastX, lastY)));
	OnRunStart();
	// tell GLFW to capture our mouse
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(m_window))
	{
		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		Draw(m_window, m_cube, w, h);
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

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);
	// Задаем цвет очистки буфера кадра
	glClearColor(1, 1, 1, 1);
}

void Window::Draw(GLFWwindow* window, Cube m_cube, int width, int height)
{
	double currentFrame = static_cast<double>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	const int lines = 20;
	const int columns = 20;

	int maze[lines][columns];

	readMazeFromFile(maze);

	processInput(window, maze);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupProjectionMatrix(width, height);
	SetupCameraMatrix(cameraPos, cameraFront, cameraUp);

	// Рисуем верхний и нижний квадраты
	glColor3f(0.99215686275, 0.91764705882, 0.85490196078);
	glRectf(0, 0, 20, 20);

	glTranslatef(0, 0, 1);

	glColor3f(0.71764705882, 0.87058823529, 0.90980392157);
	glRectf(0, 0, 20, 20);

	glTranslatef(0, 0, -1);

	//римуем стены лабиринта

	for (int y = lines - 1; y >= 0; y--)
		for (int x = columns - 1; x >= 0; x--)
		{
			if (maze[x][y] == 0)
			{
				m_cube.Draw(x, y);
			}
		}
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

void Window::processInput(GLFWwindow* window, int(maze)[20][20])
{
	glm::dvec3 front;
	glm::dvec3 futureCameraPos = cameraPos;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	double cameraSpeed = static_cast<double>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		futureCameraPos += cameraSpeed * cameraFront;
		if (!movementRestriction(futureCameraPos, maze))
		{
			cameraPos = futureCameraPos;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		futureCameraPos -= cameraSpeed * cameraFront;
		if (!movementRestriction(futureCameraPos, maze))
		{
			cameraPos = futureCameraPos;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		futureCameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (!movementRestriction(futureCameraPos, maze))
		{
			cameraPos = futureCameraPos;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		futureCameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (!movementRestriction(futureCameraPos, maze))
		{
			cameraPos = futureCameraPos;
		}
	}
		
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{

		yaw += 0.2;
		front.x = cos(glm::radians(yaw));
		front.y = sin(glm::radians(yaw));
		front.z = 0.0f;
		cameraFront = glm::normalize(front);
		cameraFront = glm::normalize(front);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{

		yaw -= 0.2;
		front.x = cos(glm::radians(yaw));
		front.y = sin(glm::radians(yaw));
		front.z = 0.0f;
		cameraFront = glm::normalize(front);
		cameraFront = glm::normalize(front);
	}
}

bool Window::movementRestriction(glm::dvec3 futureCameraPos, int(maze)[20][20])
{
	bool result = false;
	if ((futureCameraPos.x < 20) && (futureCameraPos.y < 20)
		&& (futureCameraPos.x > 0) && (futureCameraPos.y > 0))
	{
		if ((maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y - 0.2)] == 0)
			|| (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y - 0.2)] == 0))
		{
			result = true;
		}
	}
	// можно объединить условия
	if ((futureCameraPos.x > -0.2) && (futureCameraPos.x < 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < 20)
		&& (maze[(int)(futureCameraPos.x + 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.x < 20.2) && (futureCameraPos.x > 19.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < 20)
		&& (maze[(int)(futureCameraPos.x - 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y > -0.2) && (futureCameraPos.y < 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < 20)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y + 0.3)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y < 20.2) && (futureCameraPos.y > 19.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < 20)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y - 0.3)] == 0))
	{
		result = true;
	}
	return result;
}

void Window::readMazeFromFile(int(&maze)[20][20])
{
	std::ifstream input("maze.txt");
	if (input.is_open())
	{
		int x, y;
		for (x = 0; x < 20; x++)
			for (y = 0; y < 20; y++)
			{
				input >> maze[x][y];
			}
	}
	input.close();
}