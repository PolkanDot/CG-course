#define _USE_MATH_DEFINES
#include "Roof.h";
#include <stdexcept>
#include "glfw3.h"

Roof::Roof(float coordX, float coordY, float coordZ, float length, float width)
	: m_coordX(coordX)
	, m_coordY(coordY)
	, m_coordZ(coordZ)
	, m_length(length)
	, m_width(width)
{
	if ((length < 0.0) || (width < 0.0))
	{
		std::runtime_error("Size of roof can't be less than zero");
	}
}

void Roof::DrawRoof(unsigned int roofTopTexture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, roofTopTexture);
	glPushMatrix();
	{
		glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_length, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(m_length, (m_width / 2) / sin(M_PI / 4), 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, (m_width / 2) / sin(M_PI / 4), 0.0f);
		}
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, m_width, 0);
		glRotatef(135.0f, 1.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_length, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(m_length, (m_width / 2) / sin(M_PI / 4), 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, (m_width / 2) / sin(M_PI / 4), 0.0f);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}