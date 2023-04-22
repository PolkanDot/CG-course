#pragma once

/*
����� "������������ �����" ��� ������������ ���� ���������
*/
class Frame
{
public:
	// ������������� ������������� ������
	// size - ����� �������,
	Frame(float size = 1, float endSize = 0.1);

	// ������ ������������ ���
	void Draw(void) const;

private:
	float m_size;
	float m_endSize;
};
