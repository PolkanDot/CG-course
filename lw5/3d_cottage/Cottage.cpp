#define _USE_MATH_DEFINES
#include "glfw3.h"
#include "Cottage.h"
#include "Includes/glm/trigonometric.hpp"
#include <stdexcept>

Cottage::Cottage(float coordX, float coordY, float coordZ, float height)
	: m_cube()
	, m_garage(coordX, coordY + height, coordZ, height, height / 1.5, height * 0.7)
	, m_height(height)
	, m_coordX(coordX)
	, m_coordY(coordY)
	, m_coordZ(coordZ)
{
	if (height < 0.0)
	{
		std::runtime_error("Height of cottage can't be less than zero");
	}
}

Garage* Cottage::GetGarage()
{
	return &m_garage;
}

void Cottage::DrawRoof(float length, float width)
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
			glVertex3f(length, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(length, (width / 2) / sin(M_PI / 4), 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, (width / 2) / sin(M_PI / 4), 0.0f);
		}
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, width, 0);
		glRotatef(135.0f, 1.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(length, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(length, (width / 2) / sin(M_PI / 4), 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, (width / 2) / sin(M_PI / 4), 0.0f);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cottage::DrawMainHouse(float length, float width)
{
	glEnable(GL_TEXTURE_2D);
	float wallHeight = m_height * 0.7;
	m_cube.SetSize(wallHeight);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, mainHouseBottomTexture);
		glTranslatef(m_coordX, m_coordY, 0);
		glScalef(width / wallHeight, length / wallHeight, 0.7f);
		m_cube.Draw();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, cottageMidleTexture);
		glTranslatef(m_coordX, m_coordY, wallHeight * 0.7f);
		glScalef(width / wallHeight, length / wallHeight, 0.3f);
		m_cube.Draw();
	}
	glPopMatrix();
	glPushMatrix();
	{

		glBindTexture(GL_TEXTURE_2D, cottageMidleTexture);
		glTranslatef(m_coordX, m_coordY, wallHeight);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(width / 2, 0, m_height * 0.4);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(width, 0.0f, 0.0f);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(width / 2, length, m_height * 0.4);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, length, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(width, length, 0.0f);
		}
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(m_coordX + (width * 1.1), m_coordY - (width * 0.07), wallHeight * 0.89);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		DrawRoof(length * 1.1, width * 1.2);
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}



void Cottage::DrawCottage()
{
	DrawMainHouse(m_height, m_height * 0.8);
	m_garage.DrawGarage();
}