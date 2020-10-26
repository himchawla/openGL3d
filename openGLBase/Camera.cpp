
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
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	viewMat = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUpDir);
	projectionMat = glm::perspective(35.0f, 1.0f, 0.1f, 100.0f);
	timeElapsed = 0.0f;

}

void Camera::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	std::cout << timeElapsed<<std::endl;

	GLfloat radius = 20.0f;
	cameraPos.x = sin(timeElapsed) * radius;
	cameraPos.y = 1.5f;
	cameraPos.z = cos(timeElapsed) * radius;

	std::cout << cameraPos.x << "\t" << cameraPos.y << "\t" << cameraPos.z << "\n";

	//cameraUpDir.y = timeElapsed;
	
	viewMat = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUpDir);
}


//Returns Product of Projection and View Matrix
glm::mat4 Camera::getMat()
{

	glm::vec3 Scale = glm::vec3(10.0f, 10.0f, 10.0f);
	glm::vec3 Position = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 TranslationMat = glm::translate(glm::mat4(), Position);
	const glm::vec3 worldRotationAxis_Z = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotationMat = glm::rotate(glm::mat4(), glm::radians(Rotation), worldRotationAxis_Z);

	glm::mat4 scaleMat = glm::scale(glm::mat4(), Scale);

	glm::mat4 modelMat = TranslationMat * rotationMat * scaleMat;
	

	glm::mat4 worldScale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 resMat = projectionMat * viewMat * modelMat;
	return resMat;
}


//Returns Resultant Matrix
glm::mat4 Camera::project(glm::mat4 modelMat)
{
	glm::mat4 finalMat = getMat() * modelMat;
	return finalMat;
}