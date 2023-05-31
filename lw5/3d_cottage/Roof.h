#pragma once

class Roof
{
public:
	Roof(float coordX, float coordY, float coordZ, float length, float width);
	void DrawRoof(unsigned int roofTopTexture);

private:
	float m_coordX = 0;
	float m_coordY = 0;
	float m_coordZ = 0;
	float m_length = 0;
	float m_width = 0;
	float m_height = 0;
};