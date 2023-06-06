#pragma once
#include "glfw3.h"

#include <stdexcept>

class LibsInitializer final
{
public:
	LibsInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}	
	}

	LibsInitializer(const LibsInitializer&) = delete;
	LibsInitializer& operator=(const LibsInitializer&) = delete;

	~LibsInitializer()
	{
		glfwTerminate();
	}
};