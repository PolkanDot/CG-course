#include "Scene.h"
#include "Constants.h"
#include "glfw3.h"
#define STB_IMAGE_IMPLEMENTATION
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

float Scene::GetWidth()
{
	return m_width;
}

float Scene::GetLength()
{
	return m_length;
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

void Scene::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bottomTexture);
	glBegin(GL_QUADS);
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glTexCoord2f(1.0f * m_width, 0.0f);
		glVertex3f(0, m_width, 0);
		glTexCoord2f(1.0f * m_width, 1.0f * m_width);
		glVertex3f(m_width, m_width, 0);
		glTexCoord2f(0.0f, 1.0f * m_width);
		glVertex3f(m_width, 0, 0);
	}
	glEnd();


	glBindTexture(GL_TEXTURE_2D, wallTexture1);
	glPushMatrix();
	{
		//glScalef(2.0f, 1.0f, 2.0f);
		//glTranslatef(1.0f, 1.0f, 1.0f);
		m_cube.Draw();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}