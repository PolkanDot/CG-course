#include "Artist.h"

class Window
{
public:
	Window(int w, int h, const char* title)
		: m_width(w), m_height(h),m_artist(w, h)
	{
		m_window = glfwCreateWindow(w, h, title, NULL, NULL);
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	virtual ~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);
		m_artist.OnRunStart();
		int w, h;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		while (!glfwWindowShouldClose(m_window))
		{					
			glfwGetFramebufferSize(m_window, &w, &h);
			m_artist.Draw(m_artist.m_startTime, w, h);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

private:
	int m_width;
	int m_height;
	GLFWwindow* m_window;
	Artist m_artist;
};