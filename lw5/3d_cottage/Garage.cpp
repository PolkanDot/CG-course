#include "Garage.h";
#include <stdexcept>
#include "glfw3.h"

Garage::Garage(float coordX, float coordY, float coordZ, float length, float width, float height)
	: m_cube()
	, m_glass(0, 0, 0, 1, 0, 0, 1, 0)
	, m_coordX(coordX)
	, m_coordY(coordY)
	, m_coordZ(coordZ)
	, m_length(length)
    , m_width(width)
	, m_height(height)
{
	if ((length < 0.0)|| (width < 0.0)|| (height < 0.0))
	{
		std::runtime_error("Size of garage can't be less than zero");
	}
}
// Загружаем текстуры в объект Garage
void Garage::SetTextures(unsigned int cottageBottomTexture, unsigned int cottageMidleTexture, unsigned int roofTopTexture,
	unsigned int garageRoofBottomTexture, unsigned int garageDoorTexture, unsigned int windowTexture)
{
	m_cottageBottomTexture = cottageBottomTexture;
	m_cottageMidleTexture = cottageMidleTexture;
	m_roofTopTexture = roofTopTexture;
	m_garageRoofBottomTexture = garageRoofBottomTexture;
	m_garageDoorTexture = garageDoorTexture;
	m_windowTexture = windowTexture;
}
// Рисуем дверь
void Garage::DrawGarageDoor(float coordX, float coordY, float width, float height)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_garageDoorTexture);
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
// Рисуем крышу гаража
void Garage::DrawGarageRoof(float coordX, float coordY, float coordZ, float length, float width, float height)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		//Рисуем верхнюю часть из треугольников 
		glBindTexture(GL_TEXTURE_2D, m_roofTopTexture);
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
		// Рисуем нижнюю часть крыши гаража
		glBindTexture(GL_TEXTURE_2D, m_garageRoofBottomTexture);
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

void Garage::DrawGarage()
{
	glEnable(GL_TEXTURE_2D);
	float wallHeight = m_height * 0.7;
	m_cube.SetSize(wallHeight);
	// Рисуем нижнюю часть гаража
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_cottageBottomTexture);
		glTranslatef(m_coordX, m_coordY, 0);
		glScalef(m_length / wallHeight, m_width / wallHeight, 0.3f);
		m_cube.Draw();
	}
	glPopMatrix();
	// Рисуем верхнюю часть стен гаража
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_cottageMidleTexture);
		glTranslatef(m_coordX, m_coordY, wallHeight * 0.3);
		glScalef(m_length / wallHeight, m_width / wallHeight, 0.7f);
		m_cube.Draw();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Рисуем окна
	m_glass.SetPlace(m_coordX + m_length * 0.2, m_coordY + m_width + 0.0001, m_coordZ + (m_height / 3));
	m_glass.SetSize(0.5, 0.7);
	m_glass.SetDirection(0.0f, 1.0f, 0.0f);
	m_glass.DrawGlass(m_windowTexture);

	m_glass.SetPlace(m_coordX + m_length * 0.6, m_coordY + m_width + 0.0001, m_coordZ + (m_height / 3));
	m_glass.SetSize(0.5, 0.7);
	m_glass.SetDirection(0.0f, 1.0f, 0.0f);
	m_glass.DrawGlass(m_windowTexture);

	
	
	DrawGarageRoof(m_coordX - (m_width * 0.1), m_coordY - (m_width * 0.1), wallHeight, m_length * 1.1, m_width * 1.2, m_height - wallHeight);
	DrawGarageDoor(m_coordX + m_length + 0.0001, m_coordY + m_width / 2, m_width / 1.5, wallHeight * 0.8);
}