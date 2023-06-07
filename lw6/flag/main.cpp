#include "Window.h"
#include "LibsInitializer.h"

int main()
{
	LibsInitializer initLibs;
	Window window{ 1000, 800, "Flag" };
	window.Run();
}