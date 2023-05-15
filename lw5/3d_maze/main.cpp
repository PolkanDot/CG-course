#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 1000, 800, "Maze 3d" };
	window.Run();
}