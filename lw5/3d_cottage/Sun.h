#pragma once

class Sun
{
public:
	Sun(float startXCoord, float startYCord, float startZCoord, float radius, float r, float g, float b);
	void DrawCircle(float cx, float cy, float r, int num_segments);
	void DrawSun();
	
private:
	float m_theta = 1.0f;
	float m_startXCoord = 0;
	float m_startYCoord = 0;
	float m_startZCoord = 0;
	float m_radius = 1;
	float m_color[3];
	float m_position[4];
};