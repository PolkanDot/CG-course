#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#define GLEW_STATIC
#include "glew.h"

//Класс "Программный объект OpenGL"
class CProgram
{
protected:
	CProgram(GLuint program = 0)
		:m_program(program)
	{
	}

	// Деструктор программного объекта
	~CProgram();
public:

	// Создаем программный объект и возвращаем его идентификатор
	GLuint Create();

	// Выполняем замену текущего программного объекта
	CProgram& operator=(GLuint program);

	
	// Получаем целочисленный идентификатор программного объекта
	operator GLuint()const
	{
		return m_program;
	}

	// Получае целочисленный идентификатор программного объекта
	GLuint Get()const;

	// Удаляем программный объект
	void Delete();

	// Присоединям к объекту класса дескриптор программного объекта,
	// возвращая ранее существующий
	GLuint Attach(GLuint program);

	/*
	Присоединяем к программе шейдер с указанным идентификатором
	*/
	void AttachShader(GLuint shader);
	// Отсоединяем шейдер с указанным идентификатором
	void DetachShader(GLuint shader);

	// Выполняем компоновку программы
	void Link()const;

	// Проверяем, возможна ли корректная работа шейдерной программы
	// с текущим состоянием OpenGL
	void Validate()const;

	// Получаем информацию о программе в текстовом виде
	void GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const;

	// Получаем информацию о программе в текстовом виде
	// (упрощенный вариант)
	std::string GetInfoLog()const;

	// Задаем параметр программного объекта
	void GetParameter(GLenum pname, GLint* param)const;

	// Получаем расположение uniform-переменной с 
	// указанным именем
	GLint GetUniformLocation(const GLchar* name)const;

	// Получаем расположение атрибутивной переменной 
	// с заданным именем.
	GLint GetAttribLocation(const GLchar* name)const;
	// Возвращаем количество активных uniform-переменных
	GLuint GetActiveUniforms()const;

	// Возвращаем количество активных attribute-переменных
	GLuint GetActiveAttributes()const;
	// Возвращаем максимальную длину для хранения имени 
	// uniform-переменной программы
	GLuint GetActiveUniformMaxLength()const;

	// Получаем информацию об имени, типе и размере uniform-переменной
	void GetActiveUniform(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// Получаем информацию об имени, типе и размере uniform-переменной
	// более простым способом
	std::string GetActiveUniform(GLuint index, GLint* size, GLenum* type)const;

	// Возвращаем максимальную длину для хранения имени 
	// attribute-переменной программы
	GLuint GetActiveAttributeMaxLength()const;

	// Получаем информацию об имени, типе, длине и размере активной
	// attribute-переменной
	void GetActiveAttrib(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// Получаем информацию об имени, размере и типе активной
	// attribute-переменной более простым способом
	std::string GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const;

	// Получаем параметр программного объекта
	GLint GetParameter(GLenum pname)const;
private:
	CProgram(CProgram const&);
	CProgram& operator=(CProgram const&);
	GLuint m_program;
};