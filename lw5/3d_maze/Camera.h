#pragma once 
#include "glfw3.h"
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
class Camera
{
public:
	Camera(float positionX, float positionY, float positionZ, 
		float frontX, float frontY, float frontZ,
		float upX, float upY, float upZ);
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	const static int mMazeSize = 20;

	double mDeltaTime = 0.0f;
	double mLastFrame = 0.0f;

	glm::dvec3 mCameraPos;
	glm::dvec3 mCameraFront;
	glm::dvec3 mCameraUp;

	void ProcessInput(GLFWwindow* window, int(maze)[mMazeSize][mMazeSize]);

private:
	float yaw = -180.0f;
	

	
	bool MovementRestriction(glm::dvec3 futureCameraPos, int(maze)[mMazeSize][mMazeSize]);
};