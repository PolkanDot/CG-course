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

float Scene::GetSize()
{
	return m_size;
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

void Scene::DrawSun()
{
	glPushMatrix();
		// Перемещение источника света
		glTranslatef(m_size / 2, m_size / 2, 0);
		theta += 0.05f;
		glRotatef(45, 0, 0, 1);
		glRotatef(theta, 0, 1, 0);
		float position[] = { 0, 0, m_size * 0.7, 0 };
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		// Отрисовка источника света
		glPushMatrix();
			glTranslatef(0, 0, m_size * 0.7);
			glColor3f(0.5, 0.5, 0.0);
			glRectf(0, 0, 1, 1);
		glPopMatrix();
	glPopMatrix();
}

void Scene::DrawLand()
{
	glEnable(GL_TEXTURE_2D);
	// Выбираем серый цвет, чтобы был виден эффект освещения
	glColor3f(0.5, 0.5, 0.5);
	glBindTexture(GL_TEXTURE_2D, bottomTexture);
	glBegin(GL_QUADS);
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glTexCoord2f(1.0f * m_size, 0.0f);
		glVertex3f(0, m_size, 0);
		glTexCoord2f(1.0f * m_size, 1.0f * m_size);
		glVertex3f(m_size, m_size, 0);
		glTexCoord2f(0.0f, 1.0f * m_size);
		glVertex3f(m_size, 0, 0);
	}
	glEnd();
}

void Scene::DrawGarage(float coordX, float coordY, float height)
{
	glBindTexture(GL_TEXTURE_2D, wallTexture1);
	glPushMatrix();
	{
		m_cube.SetSize(height);
		glTranslatef(coordX, coordY, 1.0f);
		glScalef(2.0f, 1.0f, 1.0f);
		m_cube.Draw();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Scene::DrawCottage(float coordX, float coordY, float height)
{
	DrawGarage(coordX, coordY, height / 2);
}

void Scene::Draw()
{
	DrawSun();
	DrawLand();
	DrawCottage(0, 0, 5);
	
}