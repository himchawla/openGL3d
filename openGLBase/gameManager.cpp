
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: gameManager.h
// Description	: Class to add objects to world space
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Implementation



#include "gameManager.h"
#include"enemy.h"
#include <time.h>


//Function to reset functionality in between play sessions
void gameManager::reset()
{
	lives = 3;
	titlescreen = true;
	gameOver = false;
	victory = false;
}


int gameManager::getLives()
{
	return lives;
}

//Update function
void gameManager::Update(float dt)
{
	srand((unsigned int)time(NULL));
	unsigned int seed = 0;			//get a random seed through for enemy function
	int s = rand() % 750;
	seed += s;

	for (auto& i : enemies)					// for each element in the vector enemies
	{
		s = rand() % 750;
		seed += s;
		
		i.enMove(dt, quad.getX(), quad.getY(), seed);
		i.Update(dt);
	}

	if (level > 3)					// Victory
	{
		victory = 1;
		gameOver = 0;
	}

	if (lives <= 0)						//Defeat
	{
		gameOver = 1;
		victory = 0;
	}


	

}


void gameManager::deductLives()
{
	if (lives > 0)
		lives--;
}

void gameManager::setNumEn()
{
	numberOfEnemies--;
}


std::vector<enemy> gameManager::getEnemies()
{
	return enemies;
}

//constructor
gameManager::gameManager()
{
	res = false;
	resetTroops = false;
	currentFrame = 0;
	gameOver = 0;
	numberOfEnemies = 0;
	victory = 0;
}