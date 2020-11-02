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
#include"audio.h"

float index = 0;
float dt;				//the infamous delta time
float old_t;
float score;
void resetTroops();			//function forward declaration


audio am;
text* label;

GLuint tex;

object* cube;
object* fl;
object* bullet;
gameManager* gm;
Camera* cam;

std::vector<enemy*> enemies;

enemy* en;
int lev = 0;


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
	old_t = (float)t;

	label->Render();

	cube->Render(1);

	fl->Render(0);

	if(gm->bullet!=nullptr)
	gm->bullet->Render(0);

	for (auto i : enemies)
	{
		i->Render(0);
	}
	
	glutSwapBuffers();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


void resetTroops()								//Reset enemies
{
	
}


//update function, used to call update functions of other classes
void Update()
{
	am.update();

	bool* isPlayin = new bool;
	*isPlayin = true;
	if (am.bgChannel->isPlaying(isPlayin))
		am.bgPlay();

	score += dt;
	label->SetText("Score : " + std::to_string((int)score)+ " Lives :" +  std::to_string(gm->getLives()));

	if (gm->bullet != nullptr)
	{
		gm->bullet->bulMove(dt);
	}

	if (gm->thump)
	{
		am.play("Thump.wav");
		gm->thump = false;
	}
	//cam->Update(dt);
	gm->keyboardMove(*cube, dt);
	cam->Update(dt);

	cube->updateObject(dt);


	if (lev == 0)
	{
		lev = 1;
		for (int i = 0; i < 1; i++)
		{
			en = new enemy("Resources/Models/pug/Dog 1.obj", cam);
			//en->ObjPosition = (glm::vec3(50.0f * i, 100.0f, 100.0f * i));
			enemies.push_back(en);
		}
	}
		if (lev == 1)
		{
			if (enemies.size() == 0)
			{

				for (int i = 0; i > 3; i++)
				{
					en = new enemy("Resources/Models/pug/Dog 1.obj", cam);
					//en->ObjPosition = (glm::vec3(50.0f * i, 100.0f, 100.0f * i));
					enemies.push_back(en);
				}
			}

			for (auto& i : enemies)
			{
				
				if (glm::abs(i->ObjPosition - cube->ObjPosition).length() < 10.0f)
				{
					gm->deductLives();
				}
			//	i->enMove(dt, 100.0f, 100.0f, 200);

			}
		}
	

	//fl->updateObject(dt);
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

	
	am.audioInit();

		am.create("Background.mp3");
	am.create("Thump.wav");
	am.bgPlay();
	cube = new object("Resources/Models/Tank/Tank.obj", cam);

	fl = new object("Resources/Models/pug/ Dog 1.obj", cam);

	

	//fl->move(100.0f, 100.0f);
	//fl->objScale = glm::vec3(2.0f,2.0f,10.0f);
	//fl->objRotationAngle = glm::vec3(90.0f,45.0f,0.0f);
	

	gm = new gameManager(cam, cube, &am);

	gm->addInput();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

	label = new text("Welcome", "Resources/Fonts/ARIAL.TTF", glm::vec2(0, 48), glm::vec2(10.0f, 50.0f));

	label->SetPosition(glm::vec2(200.0f, 100.0f));
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	//glutCloseFunc(Shutdown);

	glutKeyboardFunc(gameManager::keyboardDown);
	glutKeyboardUpFunc(gameManager::keyboardUp);

	glutMainLoop();

	return 0;
}