#include "Scene.h"
#include "glfw3.h"
void Scene::Draw()
{
	glColor3f(0.99215686275, 0.91764705882, 0.85490196078);
	glRectf(0, 0, m_width, m_length);
}

float Scene::GetWidth()
{
	return m_width;
}

float Scene::GetLength()
{
	return m_length;
}