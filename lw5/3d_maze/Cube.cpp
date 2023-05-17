#include "Cube.h"
Cube::Cube()
{
	//SetSideColor(CubeSide::NEGATIVE_X, 255, 255, 255);
	//SetSideColor(CubeSide::POSITIVE_X, 255, 255, 255);
	//SetSideColor(CubeSide::NEGATIVE_Y, 255, 255, 255);
	//SetSideColor(CubeSide::POSITIVE_Y, 255, 255, 255);
	//SetSideColor(CubeSide::NEGATIVE_Z, 255, 255, 255);
	//SetSideColor(CubeSide::POSITIVE_Z, 255, 255, 255);
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
		{ 1 + x, 0 + y, 0 }, // 1
		{ 1 + x, 1 + y, 0 }, // 2
		{ 0 + x, 1 + y, 0 }, // 3
		{ 0 + x, 0 + y, 1 }, // 4
		{ 1 + x, 0 + y, 1 }, // 5
		{ 1 + x, 1 + y, 1 }, // 6
		{ 0 + x, 1 + y, 1 }, // 7
	};

	// Массив координат граней (в порядке, совпадающем с
	// порядком объявления их в массиве цветов)
	// индексы вершин граней перечисляются в порядке их обхода
	// против часовой стрелки (если смотреть на грань снаружи)
	static constexpr unsigned char faces[6][4] = {
		{ 4, 7, 3, 0 }, // грань x<0
		{ 5, 1, 2, 6 }, // грань x>0
		{ 4, 0, 1, 5 }, // грань y<0
		{ 7, 6, 2, 3 }, // грань y>0
		{ 0, 3, 2, 1 }, // грань z<0
		{ 4, 5, 6, 7 }, // грань z>0
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	
	float textVertices[4][2] =
	{
		{0.0f, 0.0f},		// 0
		{1.0f, 0.0f},		// 1
		{1.0f, 1.0f},		// 2
		{0.0f, 1.0f},		// 3
	};

	for (size_t face = 0; face < faceCount; ++face)
	{
		glBindTexture(GL_TEXTURE_2D, face);
		glBegin(GL_QUADS);
		{
			
			for (size_t i = 0; i < 4; ++i)
			{
				glTexCoord2fv(textVertices[i]);
				size_t vertexIndex = faces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
		glEnd();
	}

	// Восстанавливаем матрицу моделирования вида из стека матриц
	//glPopMatrix();
}

//void Cube::SetSideColor(CubeSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
//{
//	int index = static_cast<int>(side);
//	m_sideColors[index][0] = r;
//	m_sideColors[index][1] = g;
//	m_sideColors[index][2] = b;
//	m_sideColors[index][3] = a;
//}