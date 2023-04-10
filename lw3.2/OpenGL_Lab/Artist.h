#include "glew.h"
#include "glfw3.h"
#include <corecrt_math_defines.h>
#include <stdexcept>

class Artist
{
public:
	Artist(int w, int h)
	{
		m_window_width = w;
		m_window_height = h;
	}

	void Draw(int width, int height) const;

private:
	int m_window_width = 0;
	int m_window_height = 0;
	void DrawCircle(float cx, float cy, float r, int num_segments) const;
};