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


#include "enemy.h"
#include <time.h>

// Constructor




//movement function
void enemy::enMove(float dt, float x, float y, unsigned int seed)
{
	if (!pursuit)		//If not following
	{
		srand(seed);
		if (moveTimer <= 0.0f)
		{
			moveDir = rand() % 5;	// Choose at random which direction to move
			canMove = true;
		}

		switch (moveDir)
		{
		case 0:
		{
			setState("idle");
			if (canMove)
			{
				moveTimer = 0.1f;
				canMove = false;
			}
		}break;
		case 1:
		{
			if (getX() < 2.0f)
			{
				if (canMove)
				{
					moveTimer = 0.1f;
					canMove = false;
					setRot(0.0f);


				}
				setState("move");
				move(dt / 10.0f, 0.0f);
			}
			//	Sleep(2000);
		}break;

		case 2:
		{
			if (getX() > 0.0f)
			{
				if (canMove)
				{
					moveTimer = 0.1f;
					setRot(180.0f);

					canMove = false;
				}
				setState("move");
				move(-dt / 10.0f, 0.0f);
			}
			//	Sleep(2000);
		}break;
		case 3:
		{
			if (getY() < 2.0f)
			{
				if (canMove)
				{
					moveTimer = 0.1f;
					canMove = false;
					setState("move");
					updateObject(1);
					setRot(90.0f);


				}
				move(0.0f, dt / 10.0f);
			}
			//	Sleep(2000);
		}break;
		case 4:
		{
			if (getY() > 0.0f)
			{
				if (canMove)
				{
					moveTimer = 0.1f;
					canMove = false;
					updateObject(1);
					setRot(270.0f);

				}
				setState("move");
				move(0.0f, -dt / 10.0f);
			}
			//	Sleep(2000);
		}break;
		default:
			break;
		}
	}

	else
	{											//Code for enemy following player
		srand((unsigned int)time(NULL));
		int ch = rand() % 2;
		if (ch)
		{
			if (getX() > 0.0f && getX() < 2.0f)
			{
				if (canMove)
				{
					moveTimer = 0.1f;
					canMove = false;
				}
				setState("move");
				int decide =(int)( -1 * (getX() - x) / (abs(getX() - x)));	//normalize the distance to get the direction
				setRot(decide * -90.0f + 90.0f);
				move(decide * dt / 10.0f, 0.0f);
			}

		}

		else
		{
			if (getY() > 0.0f && getY() < 2.0f)
			{
				if (canMove)
				{
					moveTimer = 0.1f;
					canMove = false;
				}
				setState("move");
				
				std::cout << y << "\t" << getY()<<"\n";
				int decide = (int)(-1 * (getY() - y) / (abs(getY() - y)));			//normalize the distance to get the direction
				setRot(decide * -90.0f + 180.0f);
				move(0.0f, decide * dt / 10.0f);
			}
		}
	}
	updateObject(1);
}



//Update Function called every frame
void enemy::Update(float dt)
{
	if (moveTimer > 0.0f)
	{
		moveTimer -= dt/10.0f;
	}

	purTimer -= dt / 10.0f;

	if (purTimer < 0.0f)
	{
		purTimer = 0.5f;
		pursuit = !pursuit;
	}

	//updateObject(1);
}

