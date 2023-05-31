#pragma once
#include "Cube.h"
#include "Glass.h"
class Garage
{
public:
	Garage(float coordX, float coordY, float coordZ, float length, float width, float height);
	void SetTextures(unsigned int cottageBottomTexture, unsigned int cottageMidleTexture, unsigned int roofTopTexture,
		unsigned int garageRoofBottomTexture, unsigned int garageDoorTexture, unsigned int windowTexture);
	void DrawGarageDoor(float coordX, float coordY, float width, float height);
	void DrawGarageRoof(float coordX, float coordY, float coordZ, float length, float width, float height);
	void DrawGarage();
	//
	unsigned int m_cottageBottomTexture = 0;
	unsigned int m_cottageMidleTexture = 0;
	unsigned int m_roofTopTexture = 0;
	unsigned int m_garageRoofBottomTexture = 0;
	unsigned int m_garageDoorTexture = 0;
	unsigned int m_windowTexture = 0;

private:
	float m_coordX = 0;
	float m_coordY = 0;
	float m_coordZ = 0;
	float m_length = 0;
	float m_width = 0;
	float m_height = 0;

	Cube m_cube;
	Glass m_glass;
};