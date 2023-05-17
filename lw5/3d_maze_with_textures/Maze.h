#pragma once 
#include "glfw3.h"
#include "Constants.h"
#include "Cube.h"
#include <string>
class Maze
{
public:
	Maze()
		: m_cube()
	{
	}
	Maze& operator=(const Maze&) = delete;
	void ReadMazeFromFile();
	void LoadingTexture(const char* name, unsigned int& index);
	void AddFog();
	void Draw();
	int maze[mazeSize][mazeSize];
	unsigned int skyTexture;
	unsigned int bottomTexture;
	unsigned int wallTexture1;
	unsigned int wallTexture2;
	unsigned int wallTexture3;
	unsigned int wallTexture4;
private:
	Cube m_cube;
};