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
	glBindTexture(GL_TEXTURE_2D, bottomTexture);

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

	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glTranslatef(0, 0, 1);

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