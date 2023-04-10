#include "Artist.h";

void Artist::Draw(int width, int height) const
{
	DrawCircle(0, 0, 0.7, 360);
}

void Artist::DrawCircle(float cx, float cy, float r, int num_segments) const{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}