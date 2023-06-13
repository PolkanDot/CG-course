#pragma once
#include <iostream>
#include <vector>
#define GLEW_STATIC
#include "glew.h"
#include <assert.h>

//Базовый класс для работы с шейдерный объектом OpenGL

class CShader
{
	// Защищенные конструктор и деструктор сделают 
	// возможным использование данного класса только 
	// для его потомков
protected:
	CShader(GLuint shader = 0)
		:m_shader(shader)
	{
	}

	// Объявляем деструктор защищенным, т.к. в противном
	// случае компилятор сделал бы его публичным
	// Объявлять деструктор виртуальным нет необходимости
	// т.к. деструктор защищен от вызова извне, а значит
	// удалить CShaderBase напрямую не получится (только удалив
	// его наследника)
	~CShader();
public:
	// Задаем исходный код шейдера
	void SetSource(GLsizei count, const char** strings, const GLint* lengths);

	// Задаем исходный код шейдера (в одной строке)
	void SetSource(const char* source, GLint length);

	// Задаем исходный код шейдера (одна ASCIIZ-строка)
	void SetSource(const char* source);

	// Получаем значение некоторого параметра шейдера
	void GetParameter(GLenum pname, GLint* param)const;

	// Упрощенный вариант предыдущего метода
	GLint GetParameter(GLenum pname)const;

	// Получаем информационный лог от шейдера
	void GetInfoLog(GLsizei bufSize, GLsizei* length, char* infoLog)const;

	// Получаем информационный лог от шейдера
	// (упрощенный вариант)
	std::string GetInfoLog()const;

	// Получаем идентификатор шейдерного объекта
	operator GLuint()const
	{
		return m_shader;
	}

	// Получаем идентификатор шейдерного объекта (альтернативный вариант)
	GLuint Get()const;

	// Компилируем ешйдер
	void Compile();

	// Присоединяем шейдерный объект к классу и возвращаем
	// дескриптор ранее присоединенного
	GLuint Attach(GLuint shader);

	// Отсоединяем шейдерный объект
	GLuint Detach();

	// Удаляем шейдерный объект
	void Delete();

private:
	// Делаем недоступными конструктор копирования
	// и оператор присваивания
	CShader(CShader const&);
	CShader& operator=(CShader const&);
	GLuint m_shader;

	// Оператор присваивания выполняет 
	CShader& operator=(GLuint shader);

	// Создаем шейдер заданного типа
	GLuint Create(GLenum type);
};
