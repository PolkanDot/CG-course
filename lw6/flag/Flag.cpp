#include "Flag.h"
#include "glfw3.h"

void Flag::Draw()
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex2f(-0.8, -0.8);

			glTexCoord2f(4, 0);
			glVertex2f(0.8, -0.8);

			glTexCoord2f(4, 4);
			glVertex2f(0.8, 0.8);

			glTexCoord2f(0, 4);
			glVertex2f(-0.8, 0.8);

		}
	}
	glEnd();
}