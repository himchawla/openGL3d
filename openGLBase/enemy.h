
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: enemy.h
// Description	: Enemy Class inherits from object
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Local Includes


#pragma once
#include "object.h"
class enemy :
	public object
{
private:
	float moveTimer;
	float attackTimer;
	bool canMove;
	int moveDir;
	bool pursuit;
	float purTimer;

public:

	enemy();

	void enMove(float dt, float x, float y, unsigned int seed);

	

	void Update(float dt);
	void Render();
};

