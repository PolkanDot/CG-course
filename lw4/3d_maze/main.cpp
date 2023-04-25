#define _USE_MATH_DEFINES
#include "glfw3.h"
#include <chrono>
#include <cmath>
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
#include <stdexcept>

enum class CubeSide
{
	NEGATIVE_X,
	POSITIVE_X,
	NEGATIVE_Y,
	POSITIVE_Y,
	NEGATIVE_Z,
	POSITIVE_Z,
};

class Cube
{
public:
	// Создаем куб с заданной длиной стороны
	Cube(float size = 1)
	{
		SetSideColor(CubeSide::NEGATIVE_X, 255, 255, 255);
		SetSideColor(CubeSide::POSITIVE_X, 255, 255, 255);
		SetSideColor(CubeSide::NEGATIVE_Y, 255, 255, 255);
		SetSideColor(CubeSide::POSITIVE_Y, 255, 255, 255);
		SetSideColor(CubeSide::NEGATIVE_Z, 255, 255, 255);
		SetSideColor(CubeSide::POSITIVE_Z, 255, 255, 255);
	}
	// Рисуем куб
	void Draw() const
	{

		/*
		   Y
		   |
		   |
		   |
		   +---X
		  /
		 /
		Z
		   3----2
		  /    /|
		 /    / |
		7----6  |
		|  0 |  1
		|    | /
		|    |/
		4----5
		*/
		// Массив координат вершин
		static constexpr float vertices[8][3] = {
			{ 0, 0, 0 }, // 0
			{ 1, 0, 0 }, // 1
			{ 1, 1, 0 }, // 2
			{ 0, 1, 0 }, // 3
			{ 0, 0, 1 }, // 4
			{ 1, 0, 1 }, // 5
			{ 1, 1, 1 }, // 6
			{ 0, 1, 1 }, // 7
		};

		// Массив координат граней (в порядке, совпадающем с
		// порядком объявления их в массиве цветов)
		// индексы вершин граней перечисляются в порядке их обхода
		// против часовой стрелки (если смотреть на грань снаружи)
		static constexpr unsigned char faces[6][4] = {
			{ 4, 7, 3, 0 }, // грань x<0
			{ 5, 1, 2, 6 }, // грань x>0
			{ 4, 0, 1, 5 }, // грань y<0
			{ 7, 6, 2, 3 }, // грань y>0
			{ 0, 3, 2, 1 }, // грань z<0
			{ 4, 5, 6, 7 }, // грань z>0
		};
		static size_t const faceCount = sizeof(faces) / sizeof(*faces);

		// Сохраняем текущую матрицу моделирования-вида в стеке матриц
		// т.к. следующей строкой она будет модифицирована при помощи glScale
		//glPushMatrix();
		// Задаем масштабирование вершин граней
		//glScalef(m_size * 0.5f, m_size * 0.5f, m_size * 0.5f);

		glBegin(GL_QUADS);
		{
			for (size_t face = 0; face < faceCount; ++face)
			{
				// устанавливаем цвет грани
				glColor4ubv(m_sideColors[face]);

				// задаем четырехугольную грань, перечисляя ее вершины
				for (size_t i = 0; i < 4; ++i)
				{
					size_t vertexIndex = faces[face][i];
					glVertex3fv(vertices[vertexIndex]);
				}
			}
		}
		glEnd();

		// Восстанавливаем матрицу моделирования вида из стека матриц
		//glPopMatrix();
	}
	// Задаем цвет стороны куба
	void SetSideColor(CubeSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255)
	{
		int index = static_cast<int>(side);
		m_sideColors[index][0] = r;
		m_sideColors[index][1] = g;
		m_sideColors[index][2] = b;
		m_sideColors[index][3] = a;
	}

private:
	float m_size;

	// Цвета сторон куба
	GLubyte m_sideColors[6][4];
};

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
		, m_cube(CUBE_SIZE)
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
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
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
		OnRunEnd();
	}

private:
	virtual void Draw(GLFWwindow* window, Cube m_cube, int width, int height) = 0;

	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title)
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
	GLFWwindow* m_window;
	Cube m_cube;
	// Размер стороны куба
	const double CUBE_SIZE = 1;
};

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:

	glm::dvec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.5f);
	glm::dvec3 cameraFront = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::dvec3 cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);

	float yaw = 0.0f;	// yaw is initialized to -90.0 degrees since a 
	//yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;

	double deltaTime = 0.0f;	// time between current frame and last frame
	double lastFrame = 0.0f;

	void OnRunStart() override
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

	void Draw(GLFWwindow* window, Cube m_cube, int width, int height) override
	{
		double currentFrame = static_cast<double>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

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
		/*const int lines = 20;
		const int columns = 20;

		int maze[lines][columns] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		};

		*/
		m_cube.Draw();
		// Рисуем синий квадрат в плоскости Z=0, предварительно задав для него
		// трансформацию повоота вокруг оси Y и а затем переноса на 0.2 вдоль оси Z
		// Порядок умножения матриц - обратный
		float m_size = 1;
		float m_endSize = 0.1;
		float arrowOffset = m_size * m_endSize;
		float arrowOffset2 = arrowOffset * 0.5f;

		glBegin(GL_LINES);
		// Ось X
		{
			glColor3ub(255, 0, 0);

			// Рисуем ось X
			glVertex3f(0, 0, 0);
			glVertex3f(m_size, 0, 0);
			// Рисуем наконечник оси X
			glVertex3f(m_size, 0, 0);
			glVertex3f(m_size - arrowOffset, -arrowOffset2, 0);
			glVertex3f(m_size, 0, 0);
			glVertex3f(m_size - arrowOffset, +arrowOffset2, 0);
		}
		// Ось Y
		{
			glColor3ub(0, 255, 0);

			// Рисуем ось Y
			glVertex3f(0, 0, 0);
			glVertex3f(0, m_size, 0);
			// Рисуем наконечник оси Y
			glVertex3f(0, m_size, 0);
			glVertex3f(-arrowOffset2, m_size - arrowOffset, 0);
			glVertex3f(0, m_size, 0);
			glVertex3f(+arrowOffset2, m_size - arrowOffset, 0);
		}
		// Ось Z
		{
			glColor3ub(0, 0, 255);
			// Рисуем ось Z
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, m_size);
			// Рисуем наконечник оси Z
			glVertex3f(0, 0, m_size);
			glVertex3f(-arrowOffset2, 0, m_size - arrowOffset);
			glVertex3f(0, 0, m_size);
			glVertex3f(+arrowOffset2, 0, m_size - arrowOffset);
		}
		glEnd();

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

	void SetupCameraMatrix(glm::dvec3 cameraPos, glm::dvec3 cameraFront, glm::dvec3 cameraUp)
	{
		glMatrixMode(GL_MODELVIEW);
		const auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glLoadMatrixd(&view[0][0]);
	}

	void processInput(GLFWwindow* window)
	{
		glm::dvec3 front;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		double cameraSpeed = static_cast<double>(2.5 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			yaw += 0.07;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.z = sin(glm::radians(pitch));
			cameraFront = glm::normalize(front);
			cameraFront = glm::normalize(front);
		}
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{
			yaw -= 0.07;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.z = sin(glm::radians(pitch));
			cameraFront = glm::normalize(front);
			cameraFront = glm::normalize(front);
		}
	}

};

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 1000, 800, "Maze 3d" };
	window.Run();
}