#pragma once
#include "Cube.h"
#include "Garage.h"
#include "Roof.h"

class Cottage
{
public:
	Cottage(float coordX, float coordY, float coordZ, float height);
	Garage* GetGarage();
	void DrawMainHouse(float length, float width);
	
	void DrawCottage();
	// плохо
	unsigned int cottageBottomTexture = 0;
	unsigned int cottageMidleTexture = 0;
	unsigned int roofTopTexture = 0;
	unsigned int garageRoofBottomTexture = 0;
	unsigned int garageDoorTexture = 0;
	unsigned int mainHouseBottomTexture = 0;
	unsigned int windowTexture = 0;	

private:
	float m_coordX = 0;
	float m_coordY = 0;
	float m_coordZ = 0;
	float m_height = 0;
	Cube m_cube;
	Garage m_garage;
	Roof m_roof;
};