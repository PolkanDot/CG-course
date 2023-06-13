#include "CCanvas.h"
#include "glfw3.h"

void CCanvas::Draw()
{
	#define M_PI 3.1415926535897932384626433832795

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	{
		for (double x = 0; x <= 2 * M_PI; x += M_PI / 1000)
		{
			glVertex2d(x, -0.5);
		}
	}
	glEnd();
}