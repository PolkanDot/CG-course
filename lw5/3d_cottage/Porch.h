#pragma once
#include "Cube.h"
class Porch
{
public:
	Porch(float coordX, float coordY, float coordZ, float height, float width);	
	void SetPosition(float coordX, float coordY, float coordZ);
	void SetSize(float height, float width);
	void Draw(unsigned int roofTopTexture, unsigned int cottageBottomTexture, unsigned int garageDoorTexture);

private:
	float m_coordX;
	float m_coordY;
	float m_coordZ;
	float m_height;
	float m_width;

	Cube m_cube;

	void DrawDoor(unsigned int garageDoorTexture) const;
	void DrawRoof(unsigned int roofTopTexture, unsigned int cottageBottomTexture) const;
	void DrawStairs(unsigned int cottageBottomTexture);
	
};