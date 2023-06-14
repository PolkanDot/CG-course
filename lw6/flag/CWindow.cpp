#define _USE_MATH_DEFINES

#include "CWindow.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CProgramLinker.h"
//айайай разрелить файлы шейдер и программ на сипипи и аш
#include "CShader.h"
#include <chrono>
#include <cmath>

void CWindow::InitShaders()
{
	// Создаем загрузчик шейдеров
	CShaderLoader loader;
	// И загружаем с его помощью вершинный и фрагментный шейдеры
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "shaders/vertex_shader.vert");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment_shader.frag");

	// Создаем компилятор
	CShaderCompiler compiler;
	// и запускаем компиляцию шейдеров
	compiler.CompileShader(vertexShader);
	compiler.CompileShader(fragmentShader);

	// Создаем программу и присоединяем к ней шейдеры
	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	// Проверяем состояние скомпилированности шейдеров.
	// Если хотя бы один из шейдеров скомпилировался с ошибкой
	// будет выброшено исключение
	compiler.CheckStatus();
	// Все нормально, шейдеры скомпилировались без проблем

	// Создаем компоновщик,
	CProgramLinker linker;
	// компонуем программу с его помощью
	linker.LinkProgram(m_program);

	// Проверяем состояние скомпонованности программ
	// Если при компоновке возникла ошибка, то
	// будет выброшено исключение
	linker.CheckStatus();
	// Все нормально

}

GLFWwindow* CWindow::MakeWindow(int w, int h, const char* title)
{
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	return glfwCreateWindow(w, h, title, nullptr, nullptr);
}

void CWindow::Run()
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

void CWindow::OnRunStart()
{
	// Включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// Задаем цвет заливки фона
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	InitShaders();
}

void CWindow::Draw(int width, int height)
{
	// Предварительная очиствка кадра
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Переопределение матрицы проецирования
	SetupProjectionMatrix(width, height);
	glUseProgram(m_program);

	// Отрисовка флага
	m_flag.Draw();
	glUseProgram(0);
}

void CWindow::SetupProjectionMatrix(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 0, 10);
	glMatrixMode(GL_MODELVIEW);
}

