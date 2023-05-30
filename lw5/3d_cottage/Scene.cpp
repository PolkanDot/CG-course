#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include "Scene.h"
#include "Constants.h"
#include "glfw3.h"
#include "Includes/stb_image.h"
#include <iostream>
#include <fstream>

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

float Scene::GetSize()
{
	return m_size;
}

Cottage* Scene::GetCottage()
{
	return &m_cottage;
}

void Scene::LoadingTexture(const char* name, unsigned int& index)
{
	int width, height, cnt;
	unsigned char* data = stbi_load(name, &width, &height, &cnt, 0);

	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void Scene::HandlingMovement(GLFWwindow* window)
{
	m_camera.CalculateDeltaTime();
	m_camera.ProcessInput(window);
}

void Scene::DrawLand()
{
	glEnable(GL_TEXTURE_2D);
	// Выбираем серый цвет, чтобы был виден эффект освещения
	glColor3f(0.5, 0.5, 0.5);
	glBindTexture(GL_TEXTURE_2D, GetCottage()->bottomTexture);
	glBegin(GL_QUADS);
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glTexCoord2f(m_size, 0.0f);
		glVertex3f(0, m_size, 0);
		glTexCoord2f(m_size, m_size);
		glVertex3f(m_size, m_size, 0);
		glTexCoord2f(0.0f, m_size);
		glVertex3f(m_size, 0, 0);
	}
	glEnd();
}

void Scene::Draw()
{
	m_sun.DrawSun();
	DrawLand();
	m_cottage.DrawCottage(m_size / 8, m_size / 8, 4);
	
}