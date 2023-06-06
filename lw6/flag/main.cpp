#include "LibsInitializer.h"
#include "Window.h"

int main()
{
	LibsInitializer initLibs;
	Window window{ 1000, 800, "Flag" };
	window.Run();
}