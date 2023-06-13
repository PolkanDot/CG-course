#include "CShader.h"

	CShader::~CShader()
	{
		if (Get() != 0)
		{
			Delete();
		}
	}

	// ������ �������� ��� �������
	void CShader::SetSource(GLsizei count, const char** strings, const GLint* lengths)
	{
		assert(m_shader != 0);

		glShaderSource(m_shader, count, strings, lengths);
	}

	// ������ �������� ��� ������� (� ����� ������)
	void CShader::SetSource(const char* source, GLint length)
	{
		const char** ppSource = &source;
		SetSource(1, ppSource, &length);
	}

	// ������ �������� ��� ������� (���� ASCIIZ-������)
	void CShader::SetSource(const char* source)
	{
		const char** ppSource = &source;
		SetSource(1, ppSource, NULL);
	}

	// �������� �������� ���������� ��������� �������
	void CShader::GetParameter(GLenum pname, GLint* param)const
	{
		assert(m_shader != 0);
		glGetShaderiv(m_shader, pname, param);
	}

	// ���������� ������� ����������� ������
	GLint CShader::GetParameter(GLenum pname)const
	{
		GLint value;
		GetParameter(pname, &value);
		return value;
	}

	// �������� �������������� ��� �� �������
	void CShader::GetInfoLog(GLsizei bufSize, GLsizei* length, char* infoLog)const
	{
		assert(m_shader != 0);
		glGetShaderInfoLog(m_shader, bufSize, length, infoLog);
	}

	// �������� �������������� ��� �� �������
	// (���������� �������)
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

	// �������� ������������� ���������� ������� (�������������� �������)
	GLuint CShader::Get()const
	{
		return m_shader;
	}

	// ����������� ������
	void CShader::Compile()
	{
		assert(m_shader != 0);
		glCompileShader(m_shader);
	}

	// ������������ ��������� ������ � ������ � ����������
	// ���������� ����� ���������������
	GLuint CShader::Attach(GLuint shader)
	{
		GLuint tmp = m_shader;
		m_shader = shader;
		return tmp;
	}

	// ����������� ��������� ������
	GLuint CShader::Detach()
	{
		return Attach(0);
	}

	// ������� ��������� ������
	void CShader::Delete()
	{
		assert(m_shader != 0);
		if (m_shader != 0)
		{
			glDeleteShader(Detach());
			m_shader = 0;
		}
	}


	// �������� ������������ ��������� 
	CShader& CShader::operator=(GLuint shader)
	{
		// ������� ������� ��������� ������ ������ ����:
		if (
			(Get() != 0) &&		// ����� ������� ��������� ������
			(Get() != shader)	// � �� �� ��������� � ����������
			)
		{
			Delete();
		}
		Attach(shader);
		return *this;
	}

	// ������� ������ ��������� ����
	GLuint CShader::Create(GLenum type)
	{
		// ������� ������ ��������� ������ � ������ ������������� 
		// (���� �� ����� � ����� ��������� ��������)
		if (Get() != 0)
		{
			Delete();
		}
		GLuint shader = glCreateShader(type);
		Attach(shader);
		return shader;
	}
