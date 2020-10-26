
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: Camera.h
// Description	: Class to add objects to world space
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Local Includes

#pragma once

#include <glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<glew.h>
#include<freeglut.h>


class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraLookDir;
	glm::vec3 cameraUpDir;
	glm::mat4 viewMat;
	glm::mat4 projectionMat;
	float screenWidth;
	float screenHeight;
	float timeElapsed;
	float Rotation = 180.0f;

public:
	Camera();
	void Update(float deltaTime);
	glm::mat4 getMat();
	glm::mat4 project(glm::mat4 modelMat);
};

