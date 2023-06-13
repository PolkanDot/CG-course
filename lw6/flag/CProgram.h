#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#define GLEW_STATIC
#include "glew.h"

//����� "����������� ������ OpenGL"
class CProgram
{
protected:
	CProgram(GLuint program = 0)
		:m_program(program)
	{
	}

	// ���������� ������������ �������
	~CProgram();
public:

	// ������� ����������� ������ � ���������� ��� �������������
	GLuint Create();

	// ��������� ������ �������� ������������ �������
	CProgram& operator=(GLuint program);

	
	// �������� ������������� ������������� ������������ �������
	operator GLuint()const
	{
		return m_program;
	}

	// ������� ������������� ������������� ������������ �������
	GLuint Get()const;

	// ������� ����������� ������
	void Delete();

	// ����������� � ������� ������ ���������� ������������ �������,
	// ��������� ����� ������������
	GLuint Attach(GLuint program);

	/*
	������������ � ��������� ������ � ��������� ���������������
	*/
	void AttachShader(GLuint shader);
	// ����������� ������ � ��������� ���������������
	void DetachShader(GLuint shader);

	// ��������� ���������� ���������
	void Link()const;

	// ���������, �������� �� ���������� ������ ��������� ���������
	// � ������� ���������� OpenGL
	void Validate()const;

	// �������� ���������� � ��������� � ��������� ����
	void GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const;

	// �������� ���������� � ��������� � ��������� ����
	// (���������� �������)
	std::string GetInfoLog()const;

	// ������ �������� ������������ �������
	void GetParameter(GLenum pname, GLint* param)const;

	// �������� ������������ uniform-���������� � 
	// ��������� ������
	GLint GetUniformLocation(const GLchar* name)const;

	// �������� ������������ ������������ ���������� 
	// � �������� ������.
	GLint GetAttribLocation(const GLchar* name)const;
	// ���������� ���������� �������� uniform-����������
	GLuint GetActiveUniforms()const;

	// ���������� ���������� �������� attribute-����������
	GLuint GetActiveAttributes()const;
	// ���������� ������������ ����� ��� �������� ����� 
	// uniform-���������� ���������
	GLuint GetActiveUniformMaxLength()const;

	// �������� ���������� �� �����, ���� � ������� uniform-����������
	void GetActiveUniform(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// �������� ���������� �� �����, ���� � ������� uniform-����������
	// ����� ������� ��������
	std::string GetActiveUniform(GLuint index, GLint* size, GLenum* type)const;

	// ���������� ������������ ����� ��� �������� ����� 
	// attribute-���������� ���������
	GLuint GetActiveAttributeMaxLength()const;

	// �������� ���������� �� �����, ����, ����� � ������� ��������
	// attribute-����������
	void GetActiveAttrib(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// �������� ���������� �� �����, ������� � ���� ��������
	// attribute-���������� ����� ������� ��������
	std::string GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const;

	// �������� �������� ������������ �������
	GLint GetParameter(GLenum pname)const;
private:
	CProgram(CProgram const&);
	CProgram& operator=(CProgram const&);
	GLuint m_program;
};