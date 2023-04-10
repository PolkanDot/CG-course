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
		glViewport(0, 0, m_width, m_height);

		while (!glfwWindowShouldClose(m_window))
		{
			glClearColor(1.0, 1.0, 1.0, 0.5);
			glClear(GL_COLOR_BUFFER_BIT);
			m_artist.Draw();
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