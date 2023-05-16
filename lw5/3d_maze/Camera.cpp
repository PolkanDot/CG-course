#include "Camera.h"

Camera::Camera(float positionX, float positionY, float positionZ,
	float frontX, float frontY, float frontZ,
	float upX, float upY, float upZ)
{
	mCameraPos = glm::vec3(positionX, positionY, positionZ);
	mCameraFront = glm::vec3(frontX, frontY, frontZ);
	mCameraUp = glm::vec3(upX, upY, upZ);
}
// ����������� ��������� �������� "��������"
void Camera::ProcessInput(GLFWwindow* window, int(maze)[mMazeSize][mMazeSize])
{
	glm::dvec3 front;
	glm::dvec3 futureCameraPos = mCameraPos;
	// �������� ���� ����� ������� Esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	double cameraSpeed = static_cast<double>(2.5 * mDeltaTime);
	// ������ - W
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		futureCameraPos += cameraSpeed * mCameraFront;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			mCameraPos = futureCameraPos;
		}
	}
	// ����� - S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		futureCameraPos -= cameraSpeed * mCameraFront;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			mCameraPos = futureCameraPos;
		}
	}
	// ������ - A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		futureCameraPos -= glm::normalize(glm::cross(mCameraFront, mCameraUp)) * cameraSpeed;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			mCameraPos = futureCameraPos;
		}
	}
	// ������� - D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		futureCameraPos += glm::normalize(glm::cross(mCameraFront, mCameraUp)) * cameraSpeed;
		if (!MovementRestriction(futureCameraPos, maze))
		{
			mCameraPos = futureCameraPos;
		}
	}
	// �������� ������ - F	
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{

		yaw += 0.4;
		front.x = cos(glm::radians(yaw));
		front.y = sin(glm::radians(yaw));
		front.z = 0.0f;
		mCameraFront = glm::normalize(front);
		mCameraFront = glm::normalize(front);
	}
	// �������� ������� - G
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{

		yaw -= 0.4;
		front.x = cos(glm::radians(yaw));
		front.y = sin(glm::radians(yaw));
		front.z = 0.0f;
		mCameraFront = glm::normalize(front);
		mCameraFront = glm::normalize(front);
	}


}

bool Camera::MovementRestriction(glm::dvec3 futureCameraPos, int(maze)[mMazeSize][mMazeSize])
{
	bool result = false;
	// �������� �� ����������� ���� ������ ���������
	if ((futureCameraPos.x < mMazeSize) && (futureCameraPos.y < mMazeSize)
		&& (futureCameraPos.x > 0) && (futureCameraPos.y > 0))
	{
		if ((maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x + 0.2)][(int)(futureCameraPos.y - 0.2)] == 0)
			|| (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y + 0.2)] == 0) || (maze[(int)(futureCameraPos.x - 0.2)][(int)(futureCameraPos.y - 0.2)] == 0))
		{
			result = true;
		}
	}
	// �������� �� ����������� ���� ������� ���������
	if ((futureCameraPos.x > -0.2) && (futureCameraPos.x < 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < mMazeSize)
		&& (maze[(int)(futureCameraPos.x + 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.x < mMazeSize + 0.2) && (futureCameraPos.x > mMazeSize - 0.5) && (futureCameraPos.y > 0) && (futureCameraPos.y < mMazeSize)
		&& (maze[(int)(futureCameraPos.x - 0.3)][(int)(futureCameraPos.y)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y > -0.2) && (futureCameraPos.y < 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < mMazeSize)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y + 0.3)] == 0))
	{
		result = true;
	}
	if ((futureCameraPos.y < mMazeSize + 0.2) && (futureCameraPos.y > mMazeSize - 0.5) && (futureCameraPos.x > 0) && (futureCameraPos.x < mMazeSize)
		&& (maze[(int)(futureCameraPos.x)][(int)(futureCameraPos.y - 0.3)] == 0))
	{
		result = true;
	}
	return result;
}