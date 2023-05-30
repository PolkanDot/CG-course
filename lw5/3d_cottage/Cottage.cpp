#define _USE_MATH_DEFINES
#include "glfw3.h"
#include "Cottage.h"
#include "Includes/glm/trigonometric.hpp"
#include <stdexcept>

Cottage::Cottage(float coordX, float coordY, float coordZ, float height)
	: m_cube()
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

void Cottage::DrawRoof(float length, float width)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, roofTop);
	glPushMatrix();
	{
		glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, -1.0f, 1.0f);
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
		glNormal3f(0.0f, -1.0f, 1.0f);
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

void Cottage::DrawMainHouse(float coordX, float coordY, float length, float width, float height)
{
	glEnable(GL_TEXTURE_2D);
	float wallHeight = height * 0.7;
	m_cube.SetSize(wallHeight);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, mainHouseBottom);
		glTranslatef(coordX, coordY, 0);
		glScalef(width / wallHeight, length / wallHeight, 0.7f);
		m_cube.Draw();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, cottageMidleTexture);
		glTranslatef(coordX, coordY, wallHeight * 0.7f);
		glScalef(width / wallHeight, length / wallHeight, 0.3f);
		m_cube.Draw();
	}
	glPopMatrix();
	glPushMatrix();
	{

		glBindTexture(GL_TEXTURE_2D, cottageMidleTexture);
		glTranslatef(coordX, coordY, wallHeight);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(width / 2, 0, height * 0.4);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(width, 0.0f, 0.0f);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(width / 2, length, height * 0.4);
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
		glTranslatef(coordX + (width * 1.1), coordY - (width * 0.07), wallHeight * 0.89);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		DrawRoof(length * 1.1, width * 1.2);
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Cottage::DrawGarageDoor(float coordX, float coordY, float width, float height)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, garageDoor);
		glTranslatef(coordX, coordY - (width / 2), 0);
		glBegin(GL_QUADS);
		{
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0, width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, width, height);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cottage::DrawGarageRoof(float coordX, float coordY, float coordZ, float length, float width, float height)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, roofTop);
		glTranslatef(coordX, coordY, coordZ);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.5f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(length / 2, 0, height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(length, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(length, width, 0.0f);

			glNormal3f(0.0f, 1.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(length / 2, 0, height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(length, width, 0.0f);
			glTexCoord2f(2.0f, 1.0f);
			glVertex3f(0, width, 0.0f);

			glNormal3f(-0.5f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(length / 2, 0, height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, width, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0, 0, 0.0f);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, garageRoofBottom);
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(length / 2, 0.0f, height);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(length, 0.0f, 0.0f);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(length, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(length, width, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0, width, 0.0f);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Cottage::DrawGarage(float coordX, float coordY, float length, float width, float height)
{
	glEnable(GL_TEXTURE_2D);
	float wallHeight = height * 0.7;
	m_cube.SetSize(wallHeight);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, cottageBottomTexture);
		glTranslatef(coordX, coordY, 0);
		glScalef(length / wallHeight, width / wallHeight, 0.3f);
		m_cube.Draw();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, cottageMidleTexture);
		glTranslatef(coordX, coordY, wallHeight * 0.3);
		glScalef(length / wallHeight, width / wallHeight, 0.7f);
		m_cube.Draw();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	DrawGarageRoof(coordX - (width * 0.1), coordY - (width * 0.1), wallHeight, length * 1.1, width * 1.2, height - wallHeight);
	DrawGarageDoor(coordX + length + 0.0001, coordY + width / 2, width / 1.5, wallHeight * 0.8);
}

void Cottage::DrawCottage(float coordX, float coordY, float height)
{
	DrawMainHouse(coordX, coordY, height, height * 0.8, height);
	DrawGarage(coordX, coordY + height, height, height / 1.5, height * 0.7);
}