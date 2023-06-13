#include "CShader.h"

	CShader::~CShader()
	{
		if (Get() != 0)
		{
			Delete();
		}
	}

	// Задаем исходный код шейдера
	void CShader::SetSource(GLsizei count, const char** strings, const GLint* lengths)
	{
		assert(m_shader != 0);

		glShaderSource(m_shader, count, strings, lengths);
	}

	// Задаем исходный код шейдера (в одной строке)
	void CShader::SetSource(const char* source, GLint length)
	{
		const char** ppSource = &source;
		SetSource(1, ppSource, &length);
	}

	// Задаем исходный код шейдера (одна ASCIIZ-строка)
	void CShader::SetSource(const char* source)
	{
		const char** ppSource = &source;
		SetSource(1, ppSource, NULL);
	}

	// Получаем значение некоторого параметра шейдера
	void CShader::GetParameter(GLenum pname, GLint* param)const
	{
		assert(m_shader != 0);
		glGetShaderiv(m_shader, pname, param);
	}

	// Упрощенный вариант предыдущего метода
	GLint CShader::GetParameter(GLenum pname)const
	{
		GLint value;
		GetParameter(pname, &value);
		return value;
	}

	// Получаем информационный лог от шейдера
	void CShader::GetInfoLog(GLsizei bufSize, GLsizei* length, char* infoLog)const
	{
		assert(m_shader != 0);
		glGetShaderInfoLog(m_shader, bufSize, length, infoLog);
	}

	// Получаем информационный лог от шейдера
	// (упрощенный вариант)
	std::string CShader::GetInfoLog()const
	{
		GLint length = GetParameter(GL_INFO_LOG_LENGTH);
		if (length > 0)
		{
			std::vector<char> buffer(length);
			GetInfoLog(length, &length, &buffer[0]);
			std::string log(&buffer[0]);
			return log;
		}
		else
		{
			return std::string();
		}
	}

	// Получаем идентификатор шейдерного объекта (альтернативный вариант)
	GLuint CShader::Get()const
	{
		return m_shader;
	}

	// Компилируем ешйдер
	void CShader::Compile()
	{
		assert(m_shader != 0);
		glCompileShader(m_shader);
	}

	// Присоединяем шейдерный объект к классу и возвращаем
	// дескриптор ранее присоединенного
	GLuint CShader::Attach(GLuint shader)
	{
		GLuint tmp = m_shader;
		m_shader = shader;
		return tmp;
	}

	// Отсоединяем шейдерный объект
	GLuint CShader::Detach()
	{
		return Attach(0);
	}

	// Удаляем шейдерный объект
	void CShader::Delete()
	{
		assert(m_shader != 0);
		if (m_shader != 0)
		{
			glDeleteShader(Detach());
			m_shader = 0;
		}
	}


	// Оператор присваивания выполняет 
	CShader& CShader::operator=(GLuint shader)
	{
		// Удаляем текущий шейдерный объект только если:
		if (
			(Get() != 0) &&		// Задан текущий шейдерный объект
			(Get() != shader)	// И он не совпадает с переданным
			)
		{
			Delete();
		}
		Attach(shader);
		return *this;
	}

	// Создаем шейдер заданного типа
	GLuint CShader::Create(GLenum type)
	{
		// Удаляем старый шейдерный объект в случае необходимости 
		// (если он задан и класс управляет шейдером)
		if (Get() != 0)
		{
			Delete();
		}
		GLuint shader = glCreateShader(type);
		Attach(shader);
		return shader;
	}
