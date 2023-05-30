#define _USE_MATH_DEFINES
#include "Sun.h";
#include <stdexcept>
#include "glfw3.h"

Sun::Sun(float startXCoord, float startYCoord, float startZCoord, float radius, float r, float g, float b)
	: m_radius(radius)
	, m_startXCoord(startXCoord)
	, m_startYCoord(startYCoord)
	, m_startZCoord(startZCoord)
{
	if (radius < 0.0)
	{
		std::runtime_error("Radius of sun can't be less than zero");
	}
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_position[0] = 0;
	m_position[1] = 0;
	m_position[2] = startZCoord;
	m_position[3] = 0;
}

void Sun::DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);
	for (int ii = 0; ii <= num_segments; ii++) {
		float theta = 2.0f * M_PI * float(ii) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

void Sun::DrawSun()
{
	glPushMatrix();
		// Перемещение источника света
		glTranslatef(m_startXCoord, m_startYCoord, 0);
		m_theta += 0.05f;
		glRotatef(45, 0, 0, 1);
		glRotatef(m_theta, 0, 1, 0);	
		glLightfv(GL_LIGHT0, GL_POSITION, m_position);
		// Отрисовка источника света
		glPushMatrix();
			glTranslatef(0, 0, m_startZCoord);
			glColor3fv(m_color);
			DrawCircle(m_radius, m_radius, m_radius, 40);
		glPopMatrix();
	glPopMatrix();
}
