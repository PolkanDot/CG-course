#pragma once


class Scene
{
public:
	Scene(float w, float l)
	{
		m_width = w;
		m_length = l;
	}
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

	void Draw();

	float GetWidth();

	float GetLength();

private:
	float m_width;
	float m_length;

};