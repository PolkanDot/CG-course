#define STB_IMAGE_IMPLEMENTATION
#include "Includes/stb_image.h"
#include "Maze.h"
#include <iostream>
#include <fstream>

void Maze::ReadMazeFromFile()
{
	std::ifstream input("maze.txt");
	if (input.is_open())
	{
		int x, y;
		for (x = 0; x < mazeSize; x++)
			for (y = 0; y < mazeSize; y++)
			{
				input >> maze[x][y];
			}
	}
	input.close();
}

void Maze::Draw()
{	
	// Выбираем текстуру пола
	glBindTexture(GL_TEXTURE_2D, bottomTexture);
	// Рисуем пол
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(mazeSize, 0);
		glVertex3f(mazeSize, 0, 0);
		glTexCoord2f(mazeSize, mazeSize);
		glVertex3f(mazeSize, mazeSize, 0);
		glTexCoord2f(0, mazeSize);
		glVertex3f(0, mazeSize, 0);
	}
	glEnd();
	// Выбираем текстуру неба
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glTranslatef(0, 0, 1);
	// Рисуем небо
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(mazeSize, 0);
		glVertex3f(0, mazeSize, 0);
		glTexCoord2f(mazeSize, mazeSize);
		glVertex3f(mazeSize, mazeSize, 0);
		glTexCoord2f(0, mazeSize);
		glVertex3f(mazeSize, 0, 0);
	}
	glEnd();

	glTranslatef(0, 0, -1);

	//римуем стены лабиринта
	for (int y = mazeSize - 1; y >= 0; y--)
		for (int x = mazeSize - 1; x >= 0; x--)
		{
			if (maze[x][y] == 0)
			{
				m_cube.Draw(x, y);
			}
		}
}

void Maze::AddFog()
{
	float fogDensity = 0.2f;
	glFogf(GL_FOG_DENSITY, fogDensity);

	float fogStart = 0.0f;
	glFogf(GL_FOG_START, fogStart);

	float fogEnd = 10;
	glFogf(GL_FOG_END, fogEnd);

	float fogColor[] = { 0.77f, 0.77f, 0.77f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);

	glFogi(GL_FOG_MODE, GL_EXP2);

	glEnable(GL_FOG);
}

void Maze::LoadingTexture(const char* name, unsigned int& index)
{
	int width, height, cnt;
	unsigned char* data = stbi_load(name, &width, &height, &cnt, 0);

	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}