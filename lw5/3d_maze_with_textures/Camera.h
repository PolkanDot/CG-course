#pragma once 
#include "glfw3.h"
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
#include "Constants.h"
class Camera
{
public:
	Camera(float positionX, float positionY, float positionZ, 
		float frontX, float frontY, float frontZ,
		float upX, float upY, float upZ);
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	double m_deltaTime = 0.0f;
	double m_lastFrame = 0.0f;

	glm::dvec3 m_cameraPos;
	glm::dvec3 m_cameraFront;
	glm::dvec3 m_cameraUp;

	void ProcessInput(GLFWwindow* window, int(maze)[mazeSize][mazeSize]);

private:
	float m_yaw = -180.0f;
	

	
	bool MovementRestriction(glm::dvec3 futureCameraPos, int(maze)[mazeSize][mazeSize]);
};