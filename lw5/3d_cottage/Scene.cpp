#include "Scene.h"
#include "glfw3.h"
void Scene::Draw()
{
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