#pragma once
#include "glfw3.h"

#include <stdexcept>

class CLibsInitializer final
{
public:
	CLibsInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}	
	}

	CLibsInitializer(const CLibsInitializer&) = delete;
	CLibsInitializer& operator=(const CLibsInitializer&) = delete;

	~CLibsInitializer()
	{
		glfwTerminate();
	}
};