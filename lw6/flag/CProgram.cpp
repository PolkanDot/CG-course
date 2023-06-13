#include "CProgram.h"

	// ������� ������������� ������������� ������������ �������
	GLuint CProgram::Get()const
	{
		return m_program;
	}

	// ������� ����������� ������
	void CProgram::Delete()
	{
		if (m_program != 0)
		{
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	// ����������� � ������� ������ ���������� ������������ �������,
	// ��������� ����� ������������
	GLuint CProgram::Attach(GLuint program)
	{
		GLuint tmp = m_program;
		m_program = program;
		return tmp;
	}

	/*
	������������ � ��������� ������ � ��������� ���������������
	*/
	void CProgram::AttachShader(GLuint shader)
	{
		assert(m_program != 0);
		glAttachShader(m_program, shader);
	}

	// ����������� ������ � ��������� ���������������
	void CProgram::DetachShader(GLuint shader)
	{
		assert(m_program != 0);
		glDetachShader(m_program, shader);
	}

	// ��������� ���������� ���������
	void CProgram::Link()const
	{
		assert(m_program);
		glLinkProgram(m_program);
	}

	// ���������, �������� �� ���������� ������ ��������� ���������
	// � ������� ���������� OpenGL
	void CProgram::Validate()const
	{
		assert(m_program);
		glValidateProgram(m_program);
	}

	// �������� ���������� � ��������� � ��������� ����
	void CProgram::GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
	{
		assert(m_program != 0);
		glGetProgramInfoLog(m_program, bufSize, length, infoLog);
	}

	// �������� ���������� � ��������� � ��������� ����
	// (���������� �������)
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

	// ������ �������� ������������ �������
	void CProgram::GetParameter(GLenum pname, GLint* param)const
	{
		assert(m_program != 0);
		glGetProgramiv(m_program, pname, param);
	}

	// �������� ������������ uniform-���������� � 
	// ��������� ������
	GLint CProgram::GetUniformLocation(const GLchar* name)const
	{
		assert(m_program);
		return glGetUniformLocation(m_program, name);
	}

	// �������� ������������ ������������ ���������� 
	// � �������� ������.
	GLint CProgram::GetAttribLocation(const GLchar* name)const
	{
		assert(m_program);
		return glGetAttribLocation(m_program, name);
	}

	// ���������� ���������� �������� uniform-����������
	GLuint CProgram::GetActiveUniforms()const
	{
		return GetParameter(GL_ACTIVE_UNIFORMS);
	}

	// ���������� ���������� �������� attribute-����������
	GLuint CProgram::GetActiveAttributes()const
	{
		return GetParameter(GL_ACTIVE_ATTRIBUTES);
	}

	// ���������� ������������ ����� ��� �������� ����� 
	// uniform-���������� ���������
	GLuint CProgram::GetActiveUniformMaxLength()const
	{
		return GetParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH);
	}

	// �������� ���������� �� �����, ���� � ������� uniform-����������
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

	// �������� ���������� �� �����, ���� � ������� uniform-����������
	// ����� ������� ��������
	std::string CProgram::GetActiveUniform(GLuint index, GLint* size, GLenum* type)const
	{
		// ������ ������ ������ ��� �������� �����
		GLuint bufferLength = GetActiveUniformMaxLength();
		if (!bufferLength)
		{
			// ��� �������� uniform ����������
			return std::string();
		}
		std::vector<char> buffer(bufferLength);
		GLsizei nameLength = 0;

		// �������� ���, ��� � ������ ����������
		GetActiveUniform(
			index, bufferLength, &nameLength, size, type, &buffer[0]);

		// ��������� �� � ��������� �������������
		return std::string(&buffer[0], &buffer[nameLength]);
	}

	// ���������� ������������ ����� ��� �������� ����� 
	// attribute-���������� ���������
	GLuint CProgram::GetActiveAttributeMaxLength()const
	{
		return GetParameter(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
	}

	// �������� ���������� �� �����, ����, ����� � ������� ��������
	// attribute-����������
	void CProgram::GetActiveAttrib(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const
	{
		assert(m_program);
		assert(index < GetActiveAttributes());
		glGetActiveAttrib(m_program, index, maxLength, length, size, type, name);
	}

	// �������� ���������� �� �����, ������� � ���� ��������
	// attribute-���������� ����� ������� ��������
	std::string CProgram::GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const
	{
		GLuint bufferLength = GetActiveAttributeMaxLength();
		if (!bufferLength)
		{
			// ��� �������� attribute-����������
			return std::string();
		}
		std::vector<char> buffer(bufferLength);
		GLsizei nameLength = 0;

		// �������� ���, ��� � ������ ����������
		GetActiveAttrib(
			index, bufferLength,
			&nameLength, size,
			type, &buffer[0]);

		// ��������� �� � ��������� �������������
		return std::string(&buffer[0], &buffer[nameLength]);
	}

	// �������� �������� ������������ �������
	GLint CProgram::GetParameter(GLenum pname)const
	{
		GLint value = 0;
		GetParameter(pname, &value);
		return value;
	}


	// ������� ����������� ������ � ���������� ��� �������������
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

	// ��������� ������ �������� ������������ �������
	CProgram& CProgram::operator=(GLuint program)
	{
		// ������� ����� �������������� ���������
		if ((Get() != 0) && (Get() != program))
		{
			Delete();
		}
		Attach(program);
		return *this;
	}

	// ���������� ������������ �������
	CProgram::~CProgram()
	{
		// ������� ������ OpenGL (���� �� ����������� �������)
		if (Get() != 0)
		{
			Delete();
		}
	}
