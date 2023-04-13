#include "Artist.h";

void Artist::OnRunStart()
{
	this->m_startTime = std::chrono::steady_clock::now();
}

void Artist::SetupProjectionMatrix(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double aspectRatio = double(width) / double(height);
	double viewWidth = 2.0;
	double viewHeight = viewWidth;
	if (aspectRatio > 1.0)
	{
		viewWidth = viewHeight * aspectRatio;
	}
	else
	{
		viewHeight = viewWidth / aspectRatio;
	}
	glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
}

void Artist::SetupModelViewMatrix(double phase)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

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

void Artist::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float color) const {
	glBegin(GL_TRIANGLES);
	glColor3f(color, color, color);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
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

void Artist::DrawQuadrilateral(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4, float color) const {
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(color, color, color);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

/*void Artist::DrowEllipse(float centerCoordX, float centerCoordY, float rx, float ry, int pointCount, float color) const
{
	const float step = float(2 * M_PI) / pointCount;
	glColor3f(color, color, color);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerCoordX, centerCoordY);
	glRotatef(-90, 0, 0, 1);
	for (float angle = float(M_PI * -0.3); angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + centerCoordX, dy + centerCoordY);
	}
	glEnd();
}*/

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
	DrawRectangle(centerCoordX - 0.2, centerCoordY + 0.22, centerCoordX + 0.199, centerCoordY + 0.9, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.302, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.3, 40, m_rgb_gray);
	DrawRectangle(centerCoordX - 0.197, centerCoordY + 0.23, centerCoordX + 0.197, centerCoordY + 0.903, m_rgb_gray);
	DrawCircle(centerCoordX, centerCoordY, 0.272, 40, m_rgb_black);
	DrawCircle(centerCoordX, centerCoordY, 0.27, 40, m_rgb_white);
	DrawRectangle(centerCoordX - 0.162, centerCoordY + 0.22, centerCoordX + 0.162, centerCoordY + 0.8, m_rgb_black);
	DrawRectangle(centerCoordX - 0.16, centerCoordY + 0.2, centerCoordX + 0.16, centerCoordY + 0.798, m_rgb_white);
}

void Artist::DrawConnectingRod(float coordX, float coordY) const
{
	DrawQuadrilateral(coordX - 0.029, coordY + 0.01, coordX + 0.028, coordY - 0.015,
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
	DrawGradientRectangle(x1, y1, x2, y2, m_rgb_white, color);
	DrawEmptyRectangle(x1, y1, x2, y2, color);
}

void Artist::DrawCoolingFin(float x1, float y1, float x2, float y2, float color) const
{
	DrawRectangle(x1, y1, x2, y2, color);
	DrawLine(x1, y1, x2, y1, m_rgb_black);
	DrawLine(x2, y1, x2, y2, m_rgb_black);
	DrawLine(x2, y2, x1, y2, m_rgb_black);
}

void Artist::DrawCoolingFins(float centerCoordX, float centerCoordY, float color) const
{
	DrawCoolingFin(centerCoordX + 0.197, centerCoordY + 0.75, centerCoordX + 0.27, centerCoordY + 0.77, color);
	DrawCoolingFin(centerCoordX - 0.197, centerCoordY + 0.75, centerCoordX - 0.27, centerCoordY + 0.77, color);

	DrawCoolingFin(centerCoordX + 0.197, centerCoordY + 0.7, centerCoordX + 0.27, centerCoordY + 0.72, color);
	DrawCoolingFin(centerCoordX - 0.197, centerCoordY + 0.7, centerCoordX - 0.27, centerCoordY + 0.72, color);

	DrawCoolingFin(centerCoordX + 0.197, centerCoordY + 0.65, centerCoordX + 0.27, centerCoordY + 0.67, color);
	DrawCoolingFin(centerCoordX - 0.197, centerCoordY + 0.65, centerCoordX - 0.27, centerCoordY + 0.67, color);
}

void Artist::DrawValve(float coordX, float coordY, float color) const
{
	//Left
	DrawQuadrilateral(coordX + 0.215, coordY + 0.17, coordX + 0.29, coordY - 0.03,
		coordX + 0.225, coordY + 0.17, coordX + 0.3, coordY - 0.03, color);
	DrawQuadrilateral(coordX + 0.252, coordY - 0.039, coordX + 0.34, coordY - 0.014,
		coordX + 0.254, coordY - 0.047, coordX + 0.344, coordY - 0.022, color);
	//Right
	DrawQuadrilateral(coordX + 0.585, coordY + 0.17, coordX + 0.51, coordY - 0.03,
		coordX + 0.575, coordY + 0.17, coordX + 0.5, coordY - 0.03, color);
	DrawQuadrilateral(coordX + 0.548, coordY - 0.039, coordX + 0.46, coordY - 0.014,
		coordX + 0.546, coordY - 0.047, coordX + 0.456, coordY - 0.022, color);
}

void Artist::DrawUpPart(float coordX, float coordY) const
{
	DrawRectangle(coordX + 0.3, coordY - 0.05, coordX + 0.5, coordY + 0.05, m_rgb_black);

	DrawRectangle(coordX, coordY, coordX + 0.8, coordY + 0.1, m_rgb_black);
	DrawRectangle(coordX + 0.002, coordY + 0.082, coordX + 0.798, coordY + 0.098, m_rgb_gray);

	DrawRectangle(coordX + 0.002, coordY + 0.02, coordX + 0.306, coordY + 0.08, m_rgb_white);
	DrawRectangle(coordX + 0.798, coordY + 0.02, coordX + 0.494, coordY + 0.08, m_rgb_white);

	DrawRectangle(coordX + 0.002, coordY + 0.003, coordX + 0.25, coordY + 0.018, m_rgb_gray);
	DrawRectangle(coordX + 0.798, coordY + 0.003, coordX + 0.55, coordY + 0.018, m_rgb_gray);

	DrawRectangle(coordX + 0.2, coordY, coordX + 0.25, coordY + 0.018, m_rgb_gray);
	DrawRectangle(coordX + 0.6, coordY, coordX + 0.55, coordY + 0.018, m_rgb_gray);

	DrawQuadrilateral(coordX + 0.23, coordY + 0.018, coordX + 0.306, coordY + 0.08,
		coordX + 0.27, coordY - 0.1, coordX + 0.37, coordY - 0.1, m_rgb_white);
	DrawQuadrilateral(coordX + 0.57, coordY + 0.018, coordX + 0.494, coordY + 0.08,
		coordX + 0.53, coordY - 0.1, coordX + 0.43, coordY - 0.1, m_rgb_white);

	DrawLine(coordX + 0.231, coordY + 0.018, coordX + 0.252, coordY - 0.049, m_rgb_black);
	DrawLine(coordX + 0.569, coordY + 0.018, coordX + 0.548, coordY - 0.049, m_rgb_black);

	DrawRectangle(coordX + 0.255, coordY - 0.06, coordX + 0.54, coordY - 0.025, m_rgb_white);

	DrawLine(coordX + 0.345, coordY - 0.025, coordX + 0.455, coordY - 0.025, m_rgb_black);

	DrawQuadrilateral(coordX + 0.295, coordY + 0.12, coordX + 0.346, coordY - 0.025,
		coordX + 0.505, coordY + 0.12, coordX + 0.454, coordY - 0.025, m_rgb_gray);
	//Left
	DrawTriangle(coordX + 0.238, coordY + 0.09, coordX + 0.295, coordY + 0.12, coordX + 0.31, coordY + 0.09, m_rgb_gray);
	DrawLine(coordX + 0.255, coordY + 0.1, coordX + 0.295, coordY + 0.12, m_rgb_black);
	//Right
	DrawTriangle(coordX + 0.562, coordY + 0.09, coordX + 0.505, coordY + 0.12, coordX + 0.49, coordY + 0.09, m_rgb_gray);
	DrawLine(coordX + 0.545, coordY + 0.1, coordX + 0.505, coordY + 0.12, m_rgb_black);
}

void Artist::Draw(std::chrono::steady_clock::time_point m_startTime, int width, int height) const
{
	using namespace std::chrono;
	const auto currentTime = steady_clock::now();
	const auto timeSinceStart = currentTime - m_startTime;
	const auto phase = duration_cast<duration<double>>(timeSinceStart % ANIMATION_PERIOD) / ANIMATION_PERIOD;

	glClearColor(1.0, 1.0, 1.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width, height);
	SetupProjectionMatrix(width, height);
	SetupModelViewMatrix(phase);
	DrawBody(0, -0.4);
	DrawCrankShaft(0, -0.4);
	DrawConnectingRod(-0.15, -0.4);
	DrawPiston(-0.155, 0, 0.155, 0.2, m_rgb_gray);
	DrawCoolingFins(0, -0.4, m_rgb_gray);
	DrawUpPart(-0.4, 0.45);
	//DrawValve(-0.4, 0.45, m_rgb_black);
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
