#include "Artist.h";

void Artist::Draw() const
{
	DrawCrankcase(0, -0.4);
	DrawCrankShaft(0, -0.4);
}

void Artist::DrawCrankcase(float centerCoordX, float centerCoordY) const
{
	DrawCircle(centerCoordX, centerCoordY, 0.303, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.3, 40, m_rgb_gray);
	DrawCircle(centerCoordX, centerCoordY, 0.273, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.27, 40, m_rgb_white);
}

void Artist::DrawCrankShaft(float centerCoordX, float centerCoordY) const
{
	DrawHalfCircle(centerCoordX, centerCoordY, 0.24, M_PI * -0.5, 40, m_rgb_black);
	DrawQuarterCircle(centerCoordX - 0.238, centerCoordY + 0.278, 0.24, M_PI * -0.45, 40, m_rgb_black);
	DrawQuarterCircle(centerCoordX - 0.238, centerCoordY - 0.275, 0.24, M_PI * 0.05, 40, m_rgb_black);
	DrawLine(centerCoordX - 0.2, -0.36, centerCoordX - 0.2, -0.44, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.043, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.04, 40, m_rgb_gray);
}

void Artist::DrawCircle(float cx, float cy, float r, int num_segments, float color) const{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color, color, color);

	glVertex2f(cx, cy);
	for (int ii = 0; ii <= num_segments; ii++) {
		float theta = 2.0f * M_PI * float(ii) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

void Artist::DrawHalfCircle(float cx, float cy, float r, float delta, int num_segments, float color) const {
	glBegin(GL_LINE_STRIP);
	glColor3f(color, color, color);

	for (int ii = 0; ii <= num_segments; ii++) {
		float theta = M_PI * float(ii) / float(num_segments);
		float x = r * cosf(theta + delta);
		float y = r * sinf(theta + delta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

void Artist::DrawQuarterCircle(float cx, float cy, float r, float delta, int num_segments, float color) const {
	glBegin(GL_LINE_STRIP);
	glColor3f(color, color, color);

	for (int ii = 0; ii <= num_segments; ii++) {
		float theta = 0.4 * M_PI * float(ii) / float(num_segments);
		float x = r * cosf(theta + delta);
		float y = r * sinf(theta + delta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

void Artist::DrawLine(float x1, float y1, float x2, float y2, float color) const {
	glBegin(GL_LINES);
	glColor3f(color, color, color);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

/*void Artist::DrawCircumference(float cx, float cy, float r, int num_segments, float color) const {
	glBegin(GL_LINE_LOOP);
	glColor3f(color, color, color);

	for (int ii = 0; ii <= num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}*/
