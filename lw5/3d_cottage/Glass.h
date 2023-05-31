#pragma once

class Glass
{
public:
	Glass(float coordX, float coordY, float coordZ, float height, float width, 
		float directionX, float directionY, float directionZ);
	void DrawGlass(unsigned int roofTopTexture);
	void SetPlace(float coordX, float coordY, float coordZ);
	void SetSize(float height, float width);
	void SetDirection(float directionX, float directionY, float directionZ);

private:
	float m_coordX = 0;
	float m_coordY = 0;
	float m_coordZ = 0;
	float m_width = 0;
	float m_height = 0;
	float m_directionX = 0;
	float m_directionY = 0;
	float m_directionZ = 0;
};