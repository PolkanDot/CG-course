#pragma once 
#include "glfw3.h"
#include "Constants.h"
class Maze
{
public:
	Maze& operator=(const Maze&) = delete;
	void ReadMazeFromFile();
	void AddFog();
	void Draw();
	int maze[mazeSize][mazeSize];
	unsigned int skyTexture;
	unsigned int bottomTexture;
	unsigned int wallTexture1;
	unsigned int wallTexture2;
	unsigned int wallTexture3;
	unsigned int wallTexture4;
};