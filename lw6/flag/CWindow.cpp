#define _USE_MATH_DEFINES

#include "CWindow.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CProgramLinker.h"
//������ ��������� ����� ������ � �������� �� ������ � ��
#include "CShader.h"
#include <chrono>
#include <cmath>

void CWindow::InitShaders()
{
	// ������� ��������� ��������
	CShaderLoader loader;
	// � ��������� � ��� ������� ��������� � ����������� �������
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "shaders/vertex_shader.vert");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment_shader.frag");

	// ������� ����������
	CShaderCompiler compiler;
	// � ��������� ���������� ��������
	compiler.CompileShader(vertexShader);
	compiler.CompileShader(fragmentShader);

	// ������� ��������� � ������������ � ��� �������
	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	// ��������� ��������� ������������������ ��������.
	// ���� ���� �� ���� �� �������� ��������������� � �������
	// ����� ��������� ����������
	compiler.CheckStatus();
	// ��� ���������, ������� ���������������� ��� �������

	// ������� �����������,
	CProgramLinker linker;
	// ��������� ��������� � ��� �������
	linker.LinkProgram(m_program);

	// ��������� ��������� ���������������� ��������
	// ���� ��� ���������� �������� ������, ��
	// ����� ��������� ����������
	linker.CheckStatus();
	// ��� ���������

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
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ������ ���� ������� ����
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	InitShaders();
}

void CWindow::Draw(int width, int height)
{
	// ��������������� �������� �����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��������������� ������� �������������
	SetupProjectionMatrix(width, height);
	glUseProgram(m_program);

	// ��������� �����
	m_flag.Draw();
	glUseProgram(0);
}

void CWindow::SetupProjectionMatrix(int width, int height)
{
	glViewport(0, 0, width, height);

	// ��������� ����������� ������ ���������� ������� ����
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 0, 10);
	glMatrixMode(GL_MODELVIEW);
}

