#pragma once

class Fence
{
public:
	Fence(float coordX, float coordY);
	void SetPosition(float coordX, float coordY);
	void SetSize(float lenght, float height);
	void DrawFence(unsigned int fenceTexture) const;

private:
	float m_coordX;
	float m_coordY;
	float m_height;
	float m_length;
};