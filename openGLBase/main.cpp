

#include<glew.h>
#include<freeglut.h>
#include<iostream>
#include <string>
#include<vector>
#include<time.h>

//Local includes
#include "ShaderLoader.h"
#include "object.h"
#include "Camera.h"
#include "player.h"
#include"gameManager.h"
#include"object.h"
#include"enemy.h"
#include "audio.h"
#include"text.h"

float index = 0;
float dt;				//the infamous delta time
float old_t;

void resetTroops();			//function forward declaration

text* scor;
text* tilescreen;


//funtion to calculate deltatime, called in render
void calculateDT(void) {
	int t;
	/* Delta time in seconds. */
	t = glutGet(GLUT_ELAPSED_TIME);
	dt = (t - old_t)/1000.0f;
	old_t = (float)t;
	glutPostRedisplay();
}


//______________________________
object quad;
std::vector<enemy> enemies;
GLuint Program_Quad;
gameManager gm;
audio am;





int level = 0;
int lives = 3;
int numberOfEnemies;

//auto Label = new text("Welcome to Chawla's game \n Press Enter to Begin", "Resources/Fonts/Arial.ttf", glm::vec2(0, 48), glm::vec2(0.0f, 0.0f));

std::vector<GLuint> tex;

//++++++++++++++++++++++++++++++


//check collisions
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



//Rendering functio for quads
void renderCall(object& obj, GLuint& program, glm::mat4 fm, int num, std::vector<GLuint> textures, int in)
{
	glUseProgram(program);


	gm.loadCurrentState(obj, program, in);

	
	


	glUniformMatrix4fv((glGetUniformLocation(program, "finalMat")), 1, GL_FALSE, glm::value_ptr(fm));

	glBindVertexArray(obj.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Shutdown()
{
	quad.deleteBuffers();

}

//clearing enemies
void demolish()
{
	enemies.clear();
}

void Render()
{


	if (gm.titlescreen)
	{
//		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
//
		//tx->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));			//Tried text rendering, didn't work out
		//tx->SetPosition(glm::vec2(0.2f, 0.2f));
		////tx->SetScale(glm::vec2(400.0f, 400.0f));

		//tx->Render();
		
		scor->Render();
		glutSwapBuffers();
		return;

	}

	if (gm.res)			//setting variables in game manager to use here, will try not to do this in future
	{
		level = 0;
		lives = 3;
		demolish();
		gm.addAnim(quad);

		gm.res = false;
	}
	if (gm.resetTroops)						//setting variables in game manager to use here, will try not to do this in future
	{
		resetTroops();
		quad.setName("player");
		gm.addAnim(quad);

		gm.setAnimState(quad, "run");
		gm.resetTroops = false;
	}
	else if (!gm.gameOver && !gm.victory)				//Gameplay loop
	{
		unsigned int seed = 0;
		int s = rand() % 750;
		seed += s;


		for (auto& i : enemies)			
		{
			s = rand() % 750;
			seed += s;
			if (CheckCollision(i, quad))			//Collision check
			{
				if (quad.getState() == "attack")
				{
					numberOfEnemies--;					//Destroy if player is attacking
					i.absMove(10, 10);
					am.play("Thump.wav");
				}

				else {
					lives--;							//hurt the player if not attacking
					quad.absMove(0.0f, 0.0f);
				}
			}
			i.enMove(dt, quad.getX(), quad.getY(), seed);
			i.Update(dt);
		}

		calculateDT();

		glClear(GL_COLOR_BUFFER_BIT);

		index += dt * 5;

		renderCall(quad, Program_Quad, quad.finalMat, 0, quad.textures, (int)index);

		for (auto& i : enemies)
		{
			renderCall(i, Program_Quad, i.finalMat, 0, i.textures, (int)index);
		}
		scor->Render();

	}

	else if (gm.gameOver)
	{

		glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		renderCall(quad, Program_Quad, quad.finalMat, 0, quad.textures, (int)index);		//gameOver
		scor->Render();


	}

	else if(gm.victory)
	{

		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
		renderCall(quad, Program_Quad, quad.finalMat, 0, quad.textures, (int)index);		//Victory

	}
	glutSwapBuffers();
}


void resetTroops()								//Reset enemies
{
	numberOfEnemies = level * 2 + 1;
	level++;

	if (level == 4)
	{
		gm.victory = true;
	}


	enemies.clear();							//clear enemies
	for (int i = 0; i < numberOfEnemies; i++)
	{
		enemy tempEn;
		tempEn.setName("enemy");
		gm.addAnim(tempEn, 7, "idle", 1);
		gm.addAnim(tempEn, 6, "move", 1);
		gm.addAnim(tempEn, 1, "default", 1);	
		enemies.push_back(tempEn);						//push back enemies
	}
	for (auto& i : enemies)
	{
		i.genBuffers();
		int x = rand() % 20;
		int y = rand() % 20;
		//x -= 10;
		//y -= 10;

		i.absMove(x / 10.0f, y / 10.0f);
		i.setState("idle");
	}


	srand((unsigned int)time(NULL));
	
}


//update function, used to call update functions of other classes
void Update()
{
	am.update();
	bool* isPlayin = new bool;
	*isPlayin = true;
	if (am.bgChannel->isPlaying(isPlayin))
		am.bgPlay();
	if (gm.titlescreen)
	{
		quad.updateObject(1);

		gm.keyboardMove(quad, dt);				//Player movement

	}
	else if (!gm.gameOver && !gm.victory)			
	{
		gm.keyboardMove(quad, dt);
		quad.updateObject(1);
		
		if (lives <= 0)
		{
			gm.gameOver = true;
		}
		if (numberOfEnemies == 0)
		{
			resetTroops();
		}

		if (level > 3)
		{
			gm.victory = 1;
			gm.gameOver = 0;
		}

		if (lives <= 0)
		{
			gm.gameOver = 1;
			gm.victory = 0;
		}
	}

	else if (gm.victory)
	{
		gm.keyboardMove(quad, dt);

	}
	else
	{
		gm.keyboardMove(quad, dt);

	}
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("OpenGL Project");

	old_t = (float)glutGet(GLUT_ELAPSED_TIME);



	am.audioInit();
	am.create("Background.mp3");					//background music
	am.create("Thump.wav");
	am.bgPlay();

	
	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialisation has failed. Terminating. ";
		return 0;
	}
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);


	scor = new text("Welome", "Resources/Fonts/ARIAL.TTF", glm::vec2(0, 48), glm::vec2(10.0f, 50.0f));

	scor->SetPosition(glm::vec2(0.0f, 600.0f));
	quad.genBuffers();

	glm::vec3 Scale = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 Position = glm::vec3(0.5f, 0.5f, 0.0f);
	float Rotation = 180.0f;
	quad.setStuff(Position, Rotation, Scale);
	quad.setName("player");

	Position = glm::vec3(0.8f, 0.2f, 0.0f);
	

	Program_Quad = ShaderLoader::CreateProgram("Resources/Shaders/texture.vs", "Resources/Shaders/texture.fs");


	gm.addAnim(quad);

	gm.setAnimState(quad, "run");

	//quad.imageLoader("AwesomeFace", text);

	gm.addInput();
	Update();

	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	//glutCloseFunc(Shutdown);

	glutKeyboardFunc(gameManager::keyboardDown);
	glutKeyboardUpFunc(gameManager::keyboardUp);

	glutMainLoop();

	return 0;
}




