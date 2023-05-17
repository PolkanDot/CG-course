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
	unsigned int texture1;
	unsigned int texture2;
};