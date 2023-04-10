#include "Window.h";
#include <corecrt_math_defines.h>

void Window::Draw(int width, int height) const
{
	float x0 = 0;
	float y0 = 0;
	glBegin(GL_LINES);
	for (int angle = 0; angle < 360; angle += 3)
	{
		float angleInRadians = (float)(angle * M_PI / 180.0f);
		float x1 = cosf(angleInRadians);
		float y1 = sinf(angleInRadians);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
	}
	glEnd();
}