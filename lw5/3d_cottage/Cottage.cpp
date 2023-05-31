#define _USE_MATH_DEFINES
#include "glfw3.h"
#include "Cottage.h"
#include "Includes/glm/trigonometric.hpp"
#include <stdexcept>

Cottage::Cottage(float coordX, float coordY, float coordZ, float height)
	: m_cube()
	, m_garage(coordX, coordY + height, coordZ, height, height / 1.5, height * 0.7)
	, m_roof(coordX, coordY, coordZ, height * 1.1, height * 0.96)
	, m_glass(0, 0, 0, 1, 0, 0, 1, 0)
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
		m_roof.DrawRoof(roofTopTexture);
	}
	glPopMatrix();

	m_glass.SetPlace(m_coordX + (m_height * 0.8) + 0.0001, m_coordY + (m_height / 6), m_coordZ + (m_height / 5));
	m_glass.SetSize(0.7f, 1.0f);
	m_glass.SetDirection(1.0f, 0.0f, 0.0f);
	m_glass.DrawGlass(windowTexture);

	m_glass.SetPlace(m_coordX + (m_height * 0.22) + 0.0001, m_coordY - 0.0001, m_coordZ + (m_height / 5));
	m_glass.SetSize(1.0f, 1.4f);
	m_glass.SetDirection(0.0f, -1.0f, 0.0f);
	m_glass.DrawGlass(windowTexture);

	m_glass.SetPlace(m_coordX - 0.0001, m_coordY + (m_height / 6), m_coordZ + (m_height / 5));
	m_glass.SetSize(0.7f, 1.0f);
	m_glass.SetDirection(-1.0f, 0.0f, 0.0f);
	m_glass.DrawGlass(windowTexture);

	m_glass.SetPlace(m_coordX - 0.0001, m_coordY + (m_height / 1.5), m_coordZ + (m_height / 5));
	m_glass.SetSize(0.7f, 1.0f);
	m_glass.SetDirection(-1.0f, 0.0f, 0.0f);
	m_glass.DrawGlass(windowTexture);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}



void Cottage::DrawCottage()
{
	DrawMainHouse(m_height, m_height * 0.8);
	m_garage.DrawGarage();
}