#include "Flag.h"
#include "glfw3.h"

void Flag::Draw()
{
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(0.0f, 0.0f);
		glColor3f(1.0, 0.5, 0.5);
		glVertex2f(0.0f, 1.0f);
		glColor3f(0.5, 1.0, 0.5);
		glVertex2f(1.0f, 1.0f);
		//glVertex2f(1.0f, 0.0f);
	}
	glEnd();
}