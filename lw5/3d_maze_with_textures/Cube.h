#pragma once
#include "glfw3.h"
enum class CubeSide
{
	NEGATIVE_X,
	POSITIVE_X,
	NEGATIVE_Y,
	POSITIVE_Y,
	NEGATIVE_Z,
	POSITIVE_Z,
};

class Cube
{
public:
	// ������� ���
	Cube();
	// ������ ���
	void Draw(int x, int y) const;


private:
	float m_size;

	// ����� ������ ����
	//GLubyte m_sideColors[6][4];
};