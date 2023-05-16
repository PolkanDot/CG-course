#include "Camera.h"

Camera::Camera(float positionX, float positionY, float positionZ,
	float frontX, float frontY, float frontZ,
	float upX, float upY, float upZ)
{
	m_cameraPos = glm::vec3(positionX, positionY, positionZ);
	m_cameraFront = glm::vec3(frontX, frontY, frontZ);
	m_cameraUp = glm::vec3(upX, upY, upZ);
}
// ����������� ��������� �������� "��������"
void Camera::ProcessInput(GLFWwindow* window, int(maze)[m_mazeSize][m_mazeSize])
{
	glm::dvec3 front;
	glm::dvec3 futureCameraPos = m_cameraPos;
	// �������� ���� ����� ������� Esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	double cameraSpeed = static_cast<double>(2.5 * m_deltaTime);
	// ������ - W
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		futureCameraPos += cameraSpeed * m_cameraFront;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// ����� - S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		futureCameraPos -= cameraSpeed * m_cameraFront;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// ������ - A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		futureCameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// ������� - D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		futureCameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// �������� ������ - F	
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{

		yaw += 0.4;
		front.x = cos(glm::radians(yaw));
		front.y = sin(glm::radians(yaw));
		front.z = 0.0f;
		m_cameraFront = glm::normalize(front);
		m_cameraFront = glm::normalize(front);
	}
	// �������� ������� - G
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{

		yaw -= 0.4;
		front.x = cos(glm::radians(yaw));
		front.y = sin(glm::radians(yaw));
		front.z = 0.0f;
		m_cameraFront = glm::normalize(front);
		m_cameraFront = glm::normalize(front);
	}


}

bool Camera::MovementRestriction(glm::dvec3 futureCameraPos, int(maze)[m_mazeSize][m_mazeSize])
{
	bool result = false;
	// �������� �� ����������� ���� ������ ���������
	if ((futureCameraPos.x < m_mazeSize) && (futureCameraPos.y < m_mazeSize)
		&& (futureCameraPos.x > 0) && (futureCameraPos.y > 0))
	{
		if ((maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y - 0.2)] == 0)
			|| (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y - 0.2)] == 0))
		{
			result = true;
		}
	}
	// �������� �� ����������� ���� ������� ���������
	if ((futureCameraPos.x > -0.2) && (futureCameraPos.x < 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < m_mazeSize)
		&& (maze[(int)(futureCameraPos.x + 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.x < m_mazeSize + 0.2) && (futureCameraPos.x > m_mazeSize - 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < m_mazeSize)
		&& (maze[(int)(futureCameraPos.x - 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y > -0.2) && (futureCameraPos.y < 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < m_mazeSize)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y + 0.3)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y < m_mazeSize + 0.2) && (futureCameraPos.y > m_mazeSize - 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < m_mazeSize)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y - 0.3)] == 0))
	{
		result = true;
	}
	return result;
}