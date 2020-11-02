
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
#include<iostream>	

//Constructor
Camera::Camera()
{
	screenHeight = 800;
	screenWidth = 800;
	cameraPos = glm::vec3(0.0f, -3.0f, 3.0f);
	cameraLookDir = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUpDir = glm::vec3(0.0f, 0.0f, 0.0f);
	target = glm::vec3(0.0f, 1.0f, 0.0f);
	viewMat = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUpDir);
	projectionMat = glm::perspective(35.0f, 1.0f, 0.1f, 100.0f);
	timeElapsed = 0.0f;
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::updatePos(char dir, float dt)
{
	switch (dir)
	{
	case 'w':
		cameraUpDir.y = 1.0f; break;
	case 's':
		cameraUpDir.y = 1.0f; break;
	case 'a':
		cameraUpDir.y = 1.0f;	break;
	case 'd':
		cameraUpDir.y = 1.0f; break;
	}

	viewMat = glm::lookAt(cameraPos, target, cameraUpDir);
}

void Camera::Update(float deltaTime)
{
	timeElapsed += deltaTime;

//	std::cout << timeElapsed<<std::endl;

	GLfloat radius = 20.0f;
	
	/*cameraPos.x = sin(timeElapsed) * radius;
	cameraPos.y = -4.0f;
	cameraPos.z = cos(timeElapsed) * radius;*/

//	std::cout << cameraPos.x << "\t" << cameraPos.y << "\t" << cameraPos.z << "\n";

//	cameraUpDir.y = timeElapsed;
	
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - target);

//	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

//	glm::vec3 cameraUpDir = glm::cross(cameraDirection, cameraRight);

//	viewMat = glm::lookAt(cameraPos, target, up);
}



//Returns Product of Projection and View Matrix
glm::mat4 Camera::getMat()
{
	glm::mat4 resMat = projectionMat * viewMat;
	return resMat;
}


//Returns Resultant Matrix
glm::mat4 Camera::project(glm::mat4 modelMat)
{
	glm::mat4 finalMat = getMat() * modelMat;
	return	  finalMat;
}