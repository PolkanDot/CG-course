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
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(20, 0);
		glVertex3f(mazeSize, 0, 0);
		glTexCoord2f(20, 20);
		glVertex3f(mazeSize, mazeSize, 0);
		glTexCoord2f(0, 20);
		glVertex3f(0, mazeSize, 0);
	}
	glEnd();


	glTranslatef(0, 0, 1);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3f(0, mazeSize, 0);
		glTexCoord2f(1, 1);
		glVertex3f(mazeSize, mazeSize, 0);
		glTexCoord2f(0, 1);
		glVertex3f(mazeSize, 0, 0);
	}
	glEnd();

	glTranslatef(0, 0, -1);

}