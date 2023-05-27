#include "Cube.h"
#include "glfw3.h"
#include "Includes/glm/ext.hpp"
Cube::Cube(float size)
	: m_size(size)
{
}

void Cube::Draw(int x, int y) const
{

	/*
	   Y
	   |
	   |
	   |
	   +---X
	  /
	 /
	Z
	   3----2
	  /    /|
	 /    / |
	7----6  |
	|  0 |  1
	|    | /
	|    |/
	4----5
	*/
	// Массив координат вершин
	float vertices[8][3] = {
		{ 0 + x, 0 + y, 0 }, // 0
		{ m_size + x, 0 + y, 0 }, // 1
		{ m_size + x, m_size + y, 0 }, // 2
		{ 0 + x, m_size + y, 0 }, // 3
		{ 0 + x, 0 + y, m_size }, // 4
		{ m_size + x, 0 + y, m_size }, // 5
		{ m_size + x, m_size + y, m_size }, // 6
		{ 0 + x, m_size + y, m_size }, // 7
	};

	// Массив координат граней (в порядке, совпадающем с
	// порядком объявления их в массиве цветов)
	// индексы вершин граней перечисляются в порядке их обхода
	// против часовой стрелки (если смотреть на грань снаружи)
	static constexpr unsigned char faces[4][4] = {
		{ 4, 7, 3, 0 }, // грань x<0
		{ 1, 2, 6, 5 }, // грань x>0
		{ 0, 1, 5, 4 }, // грань y<0
		{ 7, 6, 2, 3 }, // грань y>0
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	float textVertices[4][2] =
	{
		{0.0f, 0.0f},		// 0
		{m_size, 0.0f},		// 1
		{m_size, m_size},	// 2
		{0.0f, m_size},		// 3
	};

	float normals[4][3] = {
		{ -1, 0, 0 }, // грань x<0
		{ 1, 0, 0 }, // грань x>0
		{ 0, -1, 0 }, // грань y<0
		{ 0, 1, 0 }, // грань y>0
	};

	for (size_t face = 0; face < faceCount; ++face)
	{
		glBegin(GL_QUADS);
		{
			glNormal3fv(normals[face]);
			for (size_t i = 0; i < 4; ++i)
			{
				glTexCoord2fv(textVertices[i]);
				size_t vertexIndex = faces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
		glEnd();
	}
}

//void Cube::Draw() const
//{	
//	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
//
//	glBegin(GL_QUADS);
//	{
//		//x+
//		glNormal3f(1.0f, 0.0f, 0.0f);
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex3f(0.5f * m_size, -0.5f * m_size, 0.5f * m_size);
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex3f(0.5f * m_size, -0.5f * m_size, -0.5f * m_size);
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(0.5f * m_size, 0.5f * m_size, -0.5f * m_size);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(0.5f * m_size, 0.5f * m_size, 0.5f * m_size);
//		//x-
//		glNormal3f(-1.0f, 0.0f, 0.0f);
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex3f(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size);
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex3f(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size);
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size);
//		// y+
//		glNormal3f(0.0f, 1.0f, 0.0f);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size);
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex3f(0.5f * m_size, 0.5f * m_size, 0.5f * m_size);
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex3f(0.5f * m_size, 0.5f * m_size, -0.5f * m_size);
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size);
//		//y-
//		glNormal3f(0.0f, -1.0f, 0.0f);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size);
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex3f(0.5f * m_size, -0.5f * m_size, -0.5f * m_size);
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex3f(0.5f * m_size, -0.5f * m_size, 0.5f * m_size);
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size);
//	}
//	glEnd();
//}

void Cube::SetSize(float size)
{
	m_size = size;
}

void Cube::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void Cube::SetShininess(float shininess)
{
	m_shininess = shininess;
}