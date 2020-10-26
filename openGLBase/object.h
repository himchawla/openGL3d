
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: object.h
// Description	: Class to make shapes and add texturing
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Local Includes


#pragma once

#include<glew.h>
#include<freeglut.h>
#include<iostream>
#include "ShaderLoader.h"
#include<vector>
#include "Camera.h"



class object
{
private:
	glm::vec3 ObjPosition;
	float objRotationAngle; 
	glm::vec3 objScale;
	std::string name;
	std::string animState;
	float speed;
	bool attack;

public:

	GLuint Program_Object;
	bool getAttack();
	void setRot(float rot);
	void setScale(float x, float y);
	
	object();

	object(bool);

	void setAttack(bool a);
	void move(float x, float y);
	void absMove(float x, float y);

	float getSpeed();
	float getX();
	float getY();
	void setSpeed(float s);

	std::string getState();
	void setState(std::string st);

	glm::mat4 updateObject(float additional);

	void Render(int in, std::vector<GLuint> t);

	struct anim 
	{
		std::vector<GLuint> tex;
		int totalFrames = 0;
		std::string name = "";
		
	};

	glm::mat4 finalMat;
	void Render(int in);
	std::string getName();
	void setName(std::string n);
	void genBuffers();
	void setBuffer();
	std::vector<GLuint> textures;
	void deleteBuffers();
	void imageLoader(std::string im, GLuint& TexNum);

	void setStuff(glm::vec3 ObjPos, float objRotAngle, glm::vec3 objSc);

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::vector<anim> getArray()
	{
		return animArray;
	}

	void addToArray(anim an)
	{
		animArray.push_back(an);
	}

	//object();
	~object();

	void setActiveTexure(int x, std::string name, std::vector<GLuint> tex, int index);

private:
	std::vector<anim> animArray;
};

