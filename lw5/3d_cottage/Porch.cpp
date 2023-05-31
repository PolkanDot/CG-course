#include "Porch.h";
#include <stdexcept>
#include "glfw3.h"

Porch::Porch(float coordX, float coordY, float coordZ, float height, float width)
	: m_coordX(coordX)
	, m_coordY(coordY)
	, m_coordZ(coordZ)
	, m_height(height)
	, m_width(width)
{
	if ((height < 0.0) || (width < 0.0))
	{
		std::runtime_error("Size of porch can't be less than zero");
	}
}

void Porch::SetPosition(float coordX, float coordY, float coordZ)
{
	m_coordX = coordX;
	m_coordY = coordY;
	m_coordZ = coordZ;
}

void Porch::SetSize(float height, float width)
{
	m_height = height;
	m_width = width;
}

void Porch::DrawDoor(unsigned int garageDoorTexture) const
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, garageDoorTexture);
		glTranslatef(m_coordX, m_coordY, m_coordZ + (m_width * 0.3));
		glBegin(GL_QUADS);
		{
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, m_width * 0.1, m_height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, m_width * 0.1, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0, m_width * 0.9, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, m_width * 0.9, m_height);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Porch::DrawRoof(unsigned int roofTopTexture, unsigned int cottageBottomTexture) const
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, roofTopTexture);
		glTranslatef(m_coordX, m_coordY, m_coordZ + m_height * 1.3);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_width / 1.5,  0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_width / 1.5, m_width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, m_width, 0.0f);
		}
		glEnd();
		glTranslatef(0, 0, -0.00001f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glBindTexture(GL_TEXTURE_2D, cottageBottomTexture);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_width / 1.5, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_width / 1.5, m_width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, m_width, 0.0f);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void Porch::DrawStairs(unsigned int cottageBottomTexture)
{
	glEnable(GL_TEXTURE_2D);
	m_cube.SetSize(m_width);
	glBindTexture(GL_TEXTURE_2D, cottageBottomTexture);

	glPushMatrix();
	{	
		glTranslatef(m_coordX, m_coordY, 0);
		glScalef(1, 1, 0.1f);
		m_cube.Draw();
		glTranslatef(0, 0, m_width);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_width, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_width, m_width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, m_width, 0.0f);
		}
		glEnd();
		glScalef(0.9f, 1.0f, 1.0f);
		m_cube.Draw();
		glTranslatef(0, 0, m_width);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_width, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_width, m_width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, m_width, 0.0f);
		}
		glEnd();
		glScalef(0.9f, 1.0f, 1.0f);
		m_cube.Draw();
		glTranslatef(0, 0, m_width);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_width, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_width, m_width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, m_width, 0.0f);
		}
		glEnd();
	}
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}

void Porch::Draw(unsigned int roofTopTexture, unsigned int cottageBottomTexture, unsigned int garageDoorTexture)
{
	DrawDoor(garageDoorTexture);
	DrawRoof(roofTopTexture, cottageBottomTexture);
	DrawStairs(cottageBottomTexture);
}