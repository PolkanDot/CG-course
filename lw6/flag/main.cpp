﻿#include "CWindow.h"
#include "CLibsInitializer.h"

int main()
{
	CLibsInitializer initLibs;
	CWindow window{ 1000, 800, "Flag" };
	window.Run();
}