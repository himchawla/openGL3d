
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
#include"Model.h"


class object:public Model
{
private:
	
	std::string name;
	std::string animState;
	float speed;
	bool attack;

public:

	bool getAttack();
	void setRot(glm::vec3 rot);
	void setScale(float x, float y);
	

	object(std::string s, Camera* cam) : Model(s, cam)
	{
		speed = 2.5f;

		glm::vec3 Scale = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 Position = glm::vec3(0.5f, 0.5f, 0.0f);
		float Rotation = 180.0f;
		camera = cam;
		setStuff(Position, glm::vec3(0.0f, 0.0f, Rotation), Scale);
	}

	void setAttack(bool a);
	void move(float x, float y);
	void absMove(float x, float y);

	float getSpeed();
	float getX();
	float getY();
	float getZ();
	void setSpeed(float s);

	std::string getState();
	void setState(std::string st);

	glm::mat4 updateObject(float additional);

	//void Render(int in, std::vector<GLuint> t);

	struct anim 
	{
		std::vector<GLuint> tex;
		int totalFrames = 0;
		std::string name = "";
		
	};

	glm::mat4 finalMat;
	//void Render(int in);
	std::string getName();
	void setName(std::string n);
	void genBuffers();
	void setBuffer();
	std::vector<GLuint> textures;
	void deleteBuffers();
	void imageLoader(std::string im, GLuint& TexNum);

	void setStuff(glm::vec3 ObjPos, glm::vec3 objRotAngle, glm::vec3 objSc);


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

