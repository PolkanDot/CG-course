#pragma once
#include "Cube.h"

class Cottage
{
public:
	Cottage(float coordX, float coordY, float coordZ, float height);
	void DrawRoof(float length, float width);
	void DrawMainHouse(float coordX, float coordY, float length, float width, float height);
	void DrawGarageDoor(float coordX, float coordY, float width, float height);
	void DrawGarageRoof(float coordX, float coordY, float coordZ, float length, float width, float height);
	void DrawGarage(float coordX, float coordY, float length, float width, float height);
	void DrawCottage(float coordX, float coordY, float height);
	// плохо
	unsigned int cottageBottomTexture = 0;
	unsigned int bottomTexture = 0;
	unsigned int cottageMidleTexture = 0;
	unsigned int roofTop = 0;
	unsigned int garageRoofBottom = 0;
	unsigned int garageDoor = 0;
	unsigned int mainHouseBottom = 0;
	unsigned int m = 0;

private:
	float m_coordX = 0;
	float m_coordY = 0;
	float m_coordZ = 0;
	float m_height = 0;
	Cube m_cube;
};