#include "Artist.h";

void Artist::DrawCircle(float cx, float cy, float r, int num_segments, float color) const {
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

void Artist::DrawRectangle(float x1, float y1, float x2, float y2, float color) const {
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(color, color, color);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glEnd();
}

void Artist::DrawEmptyRectangle(float x1, float y1, float x2, float y2, float color) const {
	glBegin(GL_LINE_LOOP);
	glColor3f(color, color, color);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}

void Artist::DrawGradientRectangle(float x1, float y1, float x2, float y2, float color1, float color2) const {
	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(color1, color1, color1, 0.9);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glColor4f(color2, color2, color2, 0.9);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void Artist::DrawRotatedRectangle(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4, float color) const {
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(color, color, color);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
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

void Artist::DrawBody(float centerCoordX, float centerCoordY) const
{
	DrawRectangle(centerCoordX - 0.2, centerCoordY + 0.22, centerCoordX + 0.199, centerCoordY + 0.8, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.302, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.3, 40, m_rgb_gray);
	DrawRectangle(centerCoordX - 0.197, centerCoordY + 0.23, 0.197, 0.403, m_rgb_gray);
	DrawCircle(centerCoordX, centerCoordY, 0.272, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.27, 40, m_rgb_white);
	DrawRectangle(centerCoordX - 0.13, centerCoordY + 0.24, centerCoordX + 0.129, centerCoordY + 0.8, m_rgb_black);
	DrawRectangle(centerCoordX - 0.127, centerCoordY + 0.24, centerCoordX + 0.127, centerCoordY + 0.8, m_rgb_white);
}

void Artist::DrawConnectingRod(float coordX, float coordY) const
{
	DrawRotatedRectangle(coordX - 0.029, coordY + 0.01, coordX + 0.028, coordY - 0.015,
		coordX + 0.122, coordY + 0.512, coordX + 0.18, coordY + 0.49, m_rgb_white);
	DrawHalfCircle(coordX, coordY, 0.03, M_PI * 0.87, 40, m_rgb_black);
	DrawCircle(coordX, coordY, 0.025, 40, m_rgb_gray);
	DrawCircle(coordX + 0.15, coordY + 0.5, 0.02, 40, m_rgb_gray);
	DrawHalfCircle(coordX + 0.15, coordY + 0.5, 0.03, M_PI * -0.13, 40, m_rgb_black);
	DrawLine(coordX - 0.029, coordY + 0.01, coordX + 0.122, coordY + 0.512, m_rgb_black);
	DrawLine(coordX + 0.028, coordY - 0.015, coordX + 0.18, coordY + 0.49, m_rgb_black);
}

void Artist::DrawPiston(float x1, float y1, float x2, float y2, float color) const
{
	DrawEmptyRectangle(x1, y1, x2, y2, color);
	DrawGradientRectangle(x1, y1, x2, y2, m_rgb_white, color);
}

void Artist::DrawCoolingFin(float x1, float y1, float x2, float y2, float color) const
{
	DrawRectangle(x1, y1, x2, y2, color);
	DrawLine(x1, y1, x2, y1, m_rgb_black);
	DrawLine(x2, y1, x2, y2, m_rgb_black);
	DrawLine(x2, y2, x1, y2, m_rgb_black);
}

void Artist::Draw() const
{
	DrawBody(0, -0.4);
	DrawCrankShaft(0, -0.4);
	DrawConnectingRod(-0.15, -0.4);
	DrawPiston(-0.125, 0, 0.125, 0.2, m_rgb_gray);
	DrawCoolingFin(0.197, 0.3, 0.25, 0.33, m_rgb_gray);
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
