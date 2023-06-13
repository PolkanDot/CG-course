#include "CProgram.h"

	// Получае целочисленный идентификатор программного объекта
	GLuint CProgram::Get()const
	{
		return m_program;
	}

	// Удаляем программный объект
	void CProgram::Delete()
	{
		if (m_program != 0)
		{
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	// Присоединям к объекту класса дескриптор программного объекта,
	// возвращая ранее существующий
	GLuint CProgram::Attach(GLuint program)
	{
		GLuint tmp = m_program;
		m_program = program;
		return tmp;
	}

	/*
	Присоединяем к программе шейдер с указанным идентификатором
	*/
	void CProgram::AttachShader(GLuint shader)
	{
		assert(m_program != 0);
		glAttachShader(m_program, shader);
	}

	// Отсоединяем шейдер с указанным идентификатором
	void CProgram::DetachShader(GLuint shader)
	{
		assert(m_program != 0);
		glDetachShader(m_program, shader);
	}

	// Выполняем компоновку программы
	void CProgram::Link()const
	{
		assert(m_program);
		glLinkProgram(m_program);
	}

	// Проверяем, возможна ли корректная работа шейдерной программы
	// с текущим состоянием OpenGL
	void CProgram::Validate()const
	{
		assert(m_program);
		glValidateProgram(m_program);
	}

	// Получаем информацию о программе в текстовом виде
	void CProgram::GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
	{
		assert(m_program != 0);
		glGetProgramInfoLog(m_program, bufSize, length, infoLog);
	}

	// Получаем информацию о программе в текстовом виде
	// (упрощенный вариант)
	std::string CProgram::GetInfoLog()const
	{
		GLint length = GetParameter(GL_INFO_LOG_LENGTH);
		if (length > 0)
		{
			std::vector<char> buffer(length);
			GetInfoLog(length, &length, &buffer[0]);
			std::string log(&buffer[0], length - 1);
			return log;
		}
		else
		{
			return std::string();
		}
	}

	// Задаем параметр программного объекта
	void CProgram::GetParameter(GLenum pname, GLint* param)const
	{
		assert(m_program != 0);
		glGetProgramiv(m_program, pname, param);
	}

	// Получаем расположение uniform-переменной с 
	// указанным именем
	GLint CProgram::GetUniformLocation(const GLchar* name)const
	{
		assert(m_program);
		return glGetUniformLocation(m_program, name);
	}

	// Получаем расположение атрибутивной переменной 
	// с заданным именем.
	GLint CProgram::GetAttribLocation(const GLchar* name)const
	{
		assert(m_program);
		return glGetAttribLocation(m_program, name);
	}

	// Возвращаем количество активных uniform-переменных
	GLuint CProgram::GetActiveUniforms()const
	{
		return GetParameter(GL_ACTIVE_UNIFORMS);
	}

	// Возвращаем количество активных attribute-переменных
	GLuint CProgram::GetActiveAttributes()const
	{
		return GetParameter(GL_ACTIVE_ATTRIBUTES);
	}

	// Возвращаем максимальную длину для хранения имени 
	// uniform-переменной программы
	GLuint CProgram::GetActiveUniformMaxLength()const
	{
		return GetParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH);
	}

	// Получаем информацию об имени, типе и размере uniform-переменной
	void CProgram::GetActiveUniform(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const
	{
		assert(m_program);
		assert(index < GetActiveUniforms());
		glGetActiveUniform(
			m_program, index, maxLength, length, size, type, name);
	}

	// Получаем информацию об имени, типе и размере uniform-переменной
	// более простым способом
	std::string CProgram::GetActiveUniform(GLuint index, GLint* size, GLenum* type)const
	{
		// Узнаем размер буфера для хранения имени
		GLuint bufferLength = GetActiveUniformMaxLength();
		if (!bufferLength)
		{
			// Нет активных uniform переменных
			return std::string();
		}
		std::vector<char> buffer(bufferLength);
		GLsizei nameLength = 0;

		// Получаем имя, тип и размер переменной
		GetActiveUniform(
			index, bufferLength, &nameLength, size, type, &buffer[0]);

		// Переводим их в строковое представление
		return std::string(&buffer[0], &buffer[nameLength]);
	}

	// Возвращаем максимальную длину для хранения имени 
	// attribute-переменной программы
	GLuint CProgram::GetActiveAttributeMaxLength()const
	{
		return GetParameter(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
	}

	// Получаем информацию об имени, типе, длине и размере активной
	// attribute-переменной
	void CProgram::GetActiveAttrib(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const
	{
		assert(m_program);
		assert(index < GetActiveAttributes());
		glGetActiveAttrib(m_program, index, maxLength, length, size, type, name);
	}

	// Получаем информацию об имени, размере и типе активной
	// attribute-переменной более простым способом
	std::string CProgram::GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const
	{
		GLuint bufferLength = GetActiveAttributeMaxLength();
		if (!bufferLength)
		{
			// Нет активных attribute-переменных
			return std::string();
		}
		std::vector<char> buffer(bufferLength);
		GLsizei nameLength = 0;

		// Получаем имя, тип и размер переменной
		GetActiveAttrib(
			index, bufferLength,
			&nameLength, size,
			type, &buffer[0]);

		// Переводим их в строковое представление
		return std::string(&buffer[0], &buffer[nameLength]);
	}

	// Получаем параметр программного объекта
	GLint CProgram::GetParameter(GLenum pname)const
	{
		GLint value = 0;
		GetParameter(pname, &value);
		return value;
	}


	// Создаем программный объект и возвращаем его идентификатор
	GLuint CProgram::Create()
	{
		if (Get() != 0)
		{
			Delete();
		}
		GLuint program = glCreateProgram();
		Attach(program);
		return program;
	}

	// Выполняем замену текущего программного объекта
	CProgram& CProgram::operator=(GLuint program)
	{
		// Удаляем ранее присоединенную программу
		if ((Get() != 0) && (Get() != program))
		{
			Delete();
		}
		Attach(program);
		return *this;
	}

	// Деструктор программного объекта
	CProgram::~CProgram()
	{
		// удаляем объект OpenGL (если он управляется классом)
		if (Get() != 0)
		{
			Delete();
		}
	}
