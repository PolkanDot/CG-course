#include "Camera.h"

Camera::Camera(float positionX, float positionY, float positionZ,
	float frontX, float frontY, float frontZ,
	float upX, float upY, float upZ)
{
	m_cameraPos = glm::vec3(positionX, positionY, positionZ);
	m_cameraFront = glm::vec3(frontX, frontY, frontZ);
	m_cameraUp = glm::vec3(upX, upY, upZ);
}

glm::dvec3 Camera::GetPos() 
{
	return m_cameraPos;
}

glm::dvec3 Camera::GetFront()
{
	return m_cameraFront;
}

glm::dvec3 Camera::GetUp()
{
	return m_cameraUp;
}

// Делаем временной шаг
void Camera::CalculateDeltaTime()
{
	double currentFrame = static_cast<double>(glfwGetTime());
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}
// Определение обработки входящих "указаний"
void Camera::ProcessInput(GLFWwindow* window)
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

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			futureCameraPos += cameraSpeed * m_cameraFront * 2.0;
		}
		
		m_cameraPos = futureCameraPos;
	}
	// Назад - S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		futureCameraPos -= cameraSpeed * m_cameraFront;
		m_cameraPos = futureCameraPos;
	}
	// Налево - A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		futureCameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		m_cameraPos = futureCameraPos;
	}
	// Направо - D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		futureCameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		m_cameraPos = futureCameraPos;
	}
	// Вверх - Т
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		futureCameraPos.z += 0.005;
		m_cameraPos = futureCameraPos;
	}
	// Вниз - G
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		futureCameraPos.z -= 0.005;
		m_cameraPos = futureCameraPos;
	}
	// Сделать, чтобы камера вращалась с одинаковой скоростью при любой ширине экрана
	// Вращение налево - F	
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{

		m_yaw += 0.4;
		front.x = cos(glm::radians(m_yaw));
		front.y = sin(glm::radians(m_yaw));
		front.z = 0.0f;
		m_cameraFront = glm::normalize(front);
	}
	// Вращение направо - H
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{

		m_yaw -= 0.4;
		front.x = cos(glm::radians(m_yaw));
		front.y = sin(glm::radians(m_yaw));
		front.z = 0.0f;
		m_cameraFront = glm::normalize(front);
	}


}
