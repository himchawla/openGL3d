
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: gameManager.h
// Description	: gameManager
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Local Includes



#pragma once

#include<glew.h>
#include<freeglut.h>

#include<vector>
#include<string>
#include "player.h"
#include "object.h"
#include "enemy.h"

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

enum inputState
{
	Input_Up,
	Input_UpFirst,
	Input_Down,
	Input_DownFirst,
};
static inputState KeyState[255];  



class gameManager
{

private:
	float AttackTimer = 0.0f;
	int z = 0;

	int level = 0;
	int lives = 3;
	int numberOfEnemies;
	std::vector<enemy> enemies;


public:
	int getNumEn();
	gameManager();
	object &getPl();
	bool res;
	bool resetTroops;
	void reset();
	bool titlescreen = true;
	bool gameOver;
	bool victory;


	bool CheckCollision(object& one, object& two) // AABB - AABB collision
	{
		// collision x-axis?
		bool collisionX = one.getX() + 0.2f >= two.getX() &&
			two.getX() + 0.2f >= one.getX();
		// collision y-axis?
		bool collisionY = one.getY() + 0.2f >= two.getY() &&
			two.getY() + 0.2f >= one.getY();
		// collision only if on both axes
		return collisionX && collisionY;
	}

	int currentFrame;

	struct input {

		unsigned char key;


		std::string name = "";
	};

	std::vector<input> inputArray;

	int getLives();
	
	void Update(float dt);
	void deductLives();
	void setNumEn();
	std::vector<enemy> getEnemies();
	bool addInput(unsigned char key, std::string name)
	{
		for (auto& i : inputArray)
		{
			if (i.name == name)
			{
				return false;
			}
		}

		input newInput = { key, name };
		inputArray.push_back(newInput);
		return true;
	}

	void addInput()
	{
		addInput('d', "moveRight");
		addInput('w', "moveTop");
		addInput('s', "moveBottom");
		addInput('a', "moveLeft");
		addInput('b', "attack");
		addInput('\r', "confirm");

	}


	static void keyboardDown(unsigned char key, int X, int Y)
	{
		KeyState[key] = Input_Down;
	}
	static void keyboardUp(unsigned char key, int X, int Y)
	{
		KeyState[key] = Input_Up;
	}



	


	std::vector<std::string> isKeyPressed(unsigned char key)
	{
		std::vector<std::string> returnStuff;
		for (auto& i : inputArray)
		{
			if (KeyState[i.key] == Input_Down)
				returnStuff.push_back(i.name);
		}
		return returnStuff;
	}


	bool isKeyDown(unsigned char key)
	{
		if (KeyState[key] == Input_Down)
			return true;                                                                                                                               
	}

	void keyboardMove(object &obj, float dt)
	{
		std::vector<std::string> tempInput;
		tempInput = isKeyPressed('0');
		AttackTimer -= dt;
		if (AttackTimer <= 0.0f)
		{
		//	obj.setState("run");
		}
		if (gameOver || victory)
		{
			reset();
			res = true;				// Resets the game after game over or victory
			gameOver = false;
			victory = false;
			titlescreen = true;
			return;
		}
	

		for (auto& i : tempInput)
		{
			
			switch (str2int(i.c_str()))
			{
			case str2int("moveRight"):
			{
				if (!gameOver && !victory && !titlescreen)
				{
					if(obj.getState()!="attack")
					obj.setState("run");
					if (obj.getX() < 2.0f)
						obj.move(dt, 0.0f);
					obj.setRot(180.0f);
					obj.setScale(-0.1f, 0.1f);
				}
			}break;
			
			case str2int("moveLeft"):
			{
				if (!gameOver && !victory && !titlescreen)
				{
					if (obj.getState() != "attack")
					obj.setState("run");
					if (obj.getX() > 0.0f)
						obj.move(-dt, 0.0f);
					obj.setRot(180.0f);
					obj.setScale(0.1f, 0.1f);
				}
			}break;

			case str2int("moveTop"):
			{
				if (!gameOver && !victory && !titlescreen)
				{
					if (obj.getState() != "attack")
					obj.setState("run");
					if (obj.getY() > 0.0f)
						obj.move(0.0f, -dt);
					obj.setRot(270.0f);
					obj.setScale(0.1f, 0.1f);
				}
			}break;
			
			case str2int("moveBottom"):
			{
				if (!gameOver && !victory && !titlescreen)
				{
					if (obj.getState() != "attack")
					obj.setState("run");
					if (obj.getY() < 2.0f)
						obj.move(0.0f, dt);
					obj.setRot(90.0f);
					obj.setScale(0.1f, 0.1f);
				}
			}break;
			case str2int("attack"):
			{
				if (!gameOver && !victory && !titlescreen)
				{
					
					obj.setAttack(true);
					AttackTimer = 3.0f;
					obj.setState("attack");
				}
			}break;

			case str2int("confirm"):
			{
				if (titlescreen)
				{
					titlescreen = false;		//Move past the title screen
					resetTroops = true;
				}
			}

			default:
			{
				obj.setState("attack");
			}

			}
		}
	}




	bool addAnim(object& obj, int num,  std::string name, bool png)
	{
		for (auto& i : obj.getArray())
		{
			if (i.name == name)
			{
				return false;
			}
		}
		std::vector<GLuint> tempTexArray;
		GLuint tempTex;
		object::anim newAnim;
		for (int i = 0; i < num; i++)
		{
			//tempTexArray.clear();
			if (!png)
				obj.imageLoader(obj.getName() + "/" + name + "/" + name + " (" + std::to_string(i + 1) + ").jpg", tempTex);
			else
				obj.imageLoader(obj.getName() + "/" + name + "/" + name + " (" + std::to_string(i + 1) + ").png", tempTex);
			
			tempTexArray.push_back(tempTex);
		}
		newAnim = { tempTexArray, num, name };

		obj.addToArray(newAnim);

		return true;
	}

	void addAnim(object &pl)
	{
		//addAnim(pl, 2, "idle", 1);
		addAnim(pl, 10, "run", 1);
		addAnim(pl, 2, "attack", 1);
		addAnim(pl, 1, "default", 1);
	}

	bool setAnimState(object& obj, std::string state)
	{
		for (auto& i : obj.getArray())
		{
			if (i.name == state)
			{
				obj.setState(state);
				return true;
			}
		}
		return false;
	}
	

	static void loadCurrentState(object& obj, GLuint prog, int in)
	{
	
		
		std::vector<GLuint> textures;

		for (auto& i : obj.getArray())
		{
			if (i.name == obj.getState())
			{
				textures = i.tex;
			}
		}

		int y = textures.size();

		int index = in - y * (in / y);

		obj.setActiveTexure(0, "textures", textures, index);


	}
	

};



