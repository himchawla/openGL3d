
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: Camera.cpp
// Description	: Class to add objects to world space
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Implementation

#include "Camera.h"


//Constructor
Camera::Camera()
{
	screenHeight = 800;
	screenWidth = 800;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	viewMat = glm::lookAt(cameraPos, cameraPos + cameraLookDir, cameraUpDir);
	projectionMat = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, 0.1f, 100.0f);

}


//Returns Product of Projection and View Matrix
glm::mat4 Camera::getMat()
{
	glm::mat4 worldScale = glm::scale(glm::mat4(), glm::vec3(400.0f, 400.0f, 1.0f));
	glm::mat4 resMat = projectionMat * viewMat * worldScale;
	return resMat;
}


//Returns Resultant Matrix
glm::mat4 Camera::project(glm::mat4 modelMat)
{
	glm::mat4 finalMat = getMat() * modelMat;
	return finalMat;
}