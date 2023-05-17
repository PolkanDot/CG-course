#include "Camera.h"

Camera::Camera(float positionX, float positionY, float positionZ,
	float frontX, float frontY, float frontZ,
	float upX, float upY, float upZ)
{
	m_cameraPos = glm::vec3(positionX, positionY, positionZ);
	m_cameraFront = glm::vec3(frontX, frontY, frontZ);
	m_cameraUp = glm::vec3(upX, upY, upZ);
}
// Определение обработки входящих "указаний"
void Camera::ProcessInput(GLFWwindow* window, int(maze)[mazeSize][mazeSize])
{
	glm::dvec3 front;
	glm::dvec3 futureCameraPos = m_cameraPos;
	// Закрытие окна после нажатия Esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	double cameraSpeed = static_cast<double>(2.5 * m_deltaTime);
	// Вперед - W
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		futureCameraPos += cameraSpeed * m_cameraFront;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// Назад - S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		futureCameraPos -= cameraSpeed * m_cameraFront;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// Налево - A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		futureCameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// Направо - D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		futureCameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			m_cameraPos = futureCameraPos;
		}
	}
	// Вращение налево - F	
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{

		m_yaw += 0.3;
		front.x = cos(glm::radians(m_yaw));
		front.y = sin(glm::radians(m_yaw));
		front.z = 0.0f;
		m_cameraFront = glm::normalize(front);
		m_cameraFront = glm::normalize(front);
	}
	// Вращение направо - G
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{

		m_yaw -= 0.3;
		front.x = cos(glm::radians(m_yaw));
		front.y = sin(glm::radians(m_yaw));
		front.z = 0.0f;
		m_cameraFront = glm::normalize(front);
		m_cameraFront = glm::normalize(front);
	}


}

bool Camera::MovementRestriction(glm::dvec3 futureCameraPos, int(maze)[mazeSize][mazeSize])
{
	bool result = false;
	// Проверка на прохождение стен внутри лабиринта
	if ((futureCameraPos.x < mazeSize) && (futureCameraPos.y < mazeSize)
		&& (futureCameraPos.x > 0) && (futureCameraPos.y > 0))
	{
		if ((maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y - 0.2)] == 0)
			|| (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y - 0.2)] == 0))
		{
			result = true;
		}
	}
	// Проверка на прохождение стен снаружи лабиринта
	if ((futureCameraPos.x > -0.2) && (futureCameraPos.x < 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < mazeSize)
		&& (maze[(int)(futureCameraPos.x + 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.x < mazeSize + 0.2) && (futureCameraPos.x > mazeSize - 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < mazeSize)
		&& (maze[(int)(futureCameraPos.x - 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y > -0.2) && (futureCameraPos.y < 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < mazeSize)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y + 0.3)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y < mazeSize + 0.2) && (futureCameraPos.y > mazeSize - 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < mazeSize)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y - 0.3)] == 0))
	{
		result = true;
	}
	return result;
}