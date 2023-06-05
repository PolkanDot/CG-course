#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 1000, 800, "Flag" };
	window.Run();
}