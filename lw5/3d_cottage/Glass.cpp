#include "Glass.h";
#include <stdexcept>
#include "glfw3.h"

Glass::Glass(float coordX, float coordY, float coordZ, float height, float width,
	float directionX, float directionY, float directionZ)
	: m_coordX(coordX)
	, m_coordY(coordY)
	, m_coordZ(coordZ)
	, m_height(height)
	, m_width(width)
	, m_directionX(directionX)
	, m_directionY(directionY)
	, m_directionZ(directionZ)
{
	if ((height < 0.0) || (width < 0.0))
	{
		std::runtime_error("Size of window can't be less than zero");
	}
}

void Glass::SetPlace(float coordX, float coordY, float coordZ)
{
	m_coordX = coordX;
	m_coordY = coordY;
	m_coordZ = coordZ;
}
void Glass::SetSize(float height, float width)
{
	m_height = height;
	m_width = width;
}

void Glass::SetDirection(float directionX, float directionY, float directionZ)
{
	m_directionX = directionX;
	m_directionY = directionY;
	m_directionZ = directionZ;
}

void Glass::DrawGlass(unsigned int windowTexture)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, windowTexture);
		glTranslatef(m_coordX, m_coordY, m_coordZ);
		glBegin(GL_QUADS);
		{
			// доработать правильную отрисовку
			glNormal3f(m_directionX, m_directionY, m_directionZ);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, m_height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0, m_width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, m_width, m_height);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}