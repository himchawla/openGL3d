#include<glew.h>
#include<freeglut.h>
#include<iostream>
#include <string>
#include<vector>
#include<time.h>

//Local includes
#include "ShaderLoader.h"
#include "object.h"
#include "player.h"
#include"gameManager.h"
#include"object.h"
#include"enemy.h"
#include "audio.h"
#include"text.h"
#include "Model.h"

float index = 0;
float dt;				//the infamous delta time
float old_t;

void resetTroops();			//function forward declaration



text* label;

GLuint tex;

object cube;

Model* model;

Camera* cam;

//Rendering functio for cubes


void Shutdown()
{
}

//clearing enemies

void Render()
{
	int t;
	/* Delta time in seconds. */
	t = glutGet(GLUT_ELAPSED_TIME);
	dt = (t - old_t)/1000.0f;
	old_t = t;

	label->Render();

	model->Render();

	
	
	glutSwapBuffers();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


void resetTroops()								//Reset enemies
{
	
}


//update function, used to call update functions of other classes
void Update()
{
	cam->Update(dt);

	
	//cube.updateObject(dt);
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("OpenGL Project");

	old_t = (float)glutGet(GLUT_ELAPSED_TIME);	
	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialisation has failed. Terminating. ";
		return 0;
	}
	cam = new Camera;

	model = new Model("Resources/Models/Tank/Tank.obj", cam);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

	label = new text("Welcome", "Resources/Fonts/ARIAL.TTF", glm::vec2(0, 48), glm::vec2(10.0f, 50.0f));

	label->SetPosition(glm::vec2(200.0f, 100.0f));
	label->SetText("You're not welcome");
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	//glutCloseFunc(Shutdown);

//	glutKeyboardFunc(gameManager::keyboardDown);
//	glutKeyboardUpFunc(gameManager::keyboardUp);

	glutMainLoop();

	return 0;
}