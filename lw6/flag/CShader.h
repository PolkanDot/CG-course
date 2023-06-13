#pragma once
#include <iostream>
#include <vector>
#define GLEW_STATIC
#include "glew.h"
#include <assert.h>

//������� ����� ��� ������ � ��������� �������� OpenGL

class CShader
{
	// ���������� ����������� � ���������� ������� 
	// ��������� ������������� ������� ������ ������ 
	// ��� ��� ��������
protected:
	CShader(GLuint shader = 0)
		:m_shader(shader)
	{
	}

	// ��������� ���������� ����������, �.�. � ���������
	// ������ ���������� ������ �� ��� ���������
	// ��������� ���������� ����������� ��� �������������
	// �.�. ���������� ������� �� ������ �����, � ������
	// ������� CShaderBase �������� �� ��������� (������ ������
	// ��� ����������)
	~CShader();
public:
	// ������ �������� ��� �������
	void SetSource(GLsizei count, const char** strings, const GLint* lengths);

	// ������ �������� ��� ������� (� ����� ������)
	void SetSource(const char* source, GLint length);

	// ������ �������� ��� ������� (���� ASCIIZ-������)
	void SetSource(const char* source);

	// �������� �������� ���������� ��������� �������
	void GetParameter(GLenum pname, GLint* param)const;

	// ���������� ������� ����������� ������
	GLint GetParameter(GLenum pname)const;

	// �������� �������������� ��� �� �������
	void GetInfoLog(GLsizei bufSize, GLsizei* length, char* infoLog)const;

	// �������� �������������� ��� �� �������
	// (���������� �������)
	std::string GetInfoLog()const;

	// �������� ������������� ���������� �������
	operator GLuint()const
	{
		return m_shader;
	}

	// �������� ������������� ���������� ������� (�������������� �������)
	GLuint Get()const;

	// ����������� ������
	void Compile();

	// ������������ ��������� ������ � ������ � ����������
	// ���������� ����� ���������������
	GLuint Attach(GLuint shader);

	// ����������� ��������� ������
	GLuint Detach();

	// ������� ��������� ������
	void Delete();

private:
	// ������ ������������ ����������� �����������
	// � �������� ������������
	CShader(CShader const&);
	CShader& operator=(CShader const&);
	GLuint m_shader;

	// �������� ������������ ��������� 
	CShader& operator=(GLuint shader);

	// ������� ������ ��������� ����
	GLuint Create(GLenum type);
};
