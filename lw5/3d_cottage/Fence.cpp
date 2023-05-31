#include "Fence.h";
#include <stdexcept>
#include <cmath>
#include "glfw3.h"

Fence::Fence(float coordX, float coordY)
	: m_coordX(coordX)
	, m_coordY(coordY)
{
}

void Fence::SetPosition(float coordX, float coordY)
{
	m_coordX = coordX;
	m_coordY = coordY;
}

void Fence::SetSize(float lenght, float height)
{
	m_height = height;
	m_length = lenght;
}

void Fence::DrawFence(unsigned int fenceTexture) const
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, fenceTexture);
		glTranslatef(m_coordX, m_coordY, 0);
		glBegin(GL_QUADS);
		{
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0, m_height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, 0, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0, m_length, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, m_length, m_height);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}