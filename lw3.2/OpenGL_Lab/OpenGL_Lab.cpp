#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 1000, 950, "Internal combustion engine" };
	window.Run();
}