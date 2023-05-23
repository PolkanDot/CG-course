#include "Scene.h"
#include "glfw3.h"

glm::dvec3 Scene::GetCameraPos()
{
	return m_camera.GetPos();
}

glm::dvec3 Scene::GetCameraFront()
{
	return m_camera.GetFront();
}

glm::dvec3 Scene::GetCameraUp()
{
	return m_camera.GetUp();
}

void Scene::HandlingMovement(GLFWwindow* window)
{
	m_camera.CalculateDeltaTime();
	m_camera.ProcessInput(window);
}

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