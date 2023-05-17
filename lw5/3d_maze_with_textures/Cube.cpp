#include "Cube.h"

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
	// ћассив координат вершин
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

	// ћассив координат граней (в пор€дке, совпадающем с
	// пор€дком объ€влени€ их в массиве цветов)
	// индексы вершин граней перечисл€ютс€ в пор€дке их обхода
	// против часовой стрелки (если смотреть на грань снаружи)
	static constexpr unsigned char faces[4][4] = {
		{ 4, 7, 3, 0 }, // грань x<0
		{ 5, 1, 2, 6 }, // грань x>0
		{ 4, 0, 1, 5 }, // грань y<0
		{ 7, 6, 2, 3 }, // грань y>0
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
		glBindTexture(GL_TEXTURE_2D, face + 3);
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
}
