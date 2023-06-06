#include "Flag.h"
#include "glfw3.h"

void Flag::Draw()
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	{
		glBegin(GL_QUADS);
		{
			glVertex2f(-0.8, -0.8);
			glVertex2f(0.8, -0.8);
			glVertex2f(0.8, 0.8);
			glVertex2f(-0.8, 0.8);
		}
	}
	glEnd();
}