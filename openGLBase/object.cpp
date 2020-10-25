//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: object.cpp
// Description	: Class to make shapes and add texturing
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Implementation


#include "object.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include "gameManager.h"

Camera cam1;

GLuint Indices_Quad[] =
{
   0,1,2,
   0,2,3,
};


GLfloat Vertices_Quad[] =
{
	//Position						//Color						//Texture Coordinates
	-1.0f,	1.0f,	0.0f,			1.0f,0.0f,0.0f,				0.0f,0.0f,
	-1.0f,	-1.0f,	0.0f,			0.0f,1.0f,0.0f,				0.0f,1.0f,
	 1.0f,	-1.0f,	0.0f,			0.0f,0.0f,1.0f,				1.0f,1.0f,
	 1.0f,	 1.0f,	0.0f,			1.0f,1.0f,1.0f,				1.0f,0.0f,
};

//generate Buffers, called during setup phase
void object::genBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices_Quad), Indices_Quad, GL_STATIC_DRAW);

	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Quad), Vertices_Quad, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	
}

//Bind Buffers, called once per frame
void object::setBuffer()
{
	

	

}


//Generate Buffers for quad, called in setup mode
//Bind buffers for quad, called once per frame
//Delete buffers, called at end of the code

void object::deleteBuffers()
{
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}





object::object()
{
	
}

object::object(bool)
{
	speed = 2.5f;

	glm::vec3 Scale = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 Position = glm::vec3(0.5f, 0.5f, 0.0f);
	float Rotation = 180.0f;
	setStuff(Position, Rotation, Scale);
	Program_Object = ShaderLoader::CreateProgram("Resources/Shaders/texture.vs", "Resources/Shaders/texture.fs");
}

//Deconstructor
object::~object()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}

void object::setActiveTexure(GLuint Program, int x, std::string name, std::vector<GLuint> tex, int index)
{
	int y = tex.size();
	glActiveTexture(33984 + x);		// GL_TEXTUR0 = 33984

	
	int in = index - y * (index / y);
	glBindTexture(GL_TEXTURE_2D, tex[in]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUniform1i(glGetUniformLocation(Program, name.c_str()), x);
}

std::string object::getName()
{
	return name;
}

void object::setName(std::string n)
{
	name = n;
}

bool object::getAttack()
{
	return attack;
}

void object::setRot(float rot)
{
	objRotationAngle = rot;
}

void object::setScale(float x, float y)
{
	objScale.x = x;
	objScale.y = y;
}

void object::setAttack(bool a)
{
	attack = a;
}

void object::move(float x, float y)
{
	ObjPosition.x += x * speed;
	ObjPosition.y += y * speed;
}

void object::absMove(float x, float y)
{
	ObjPosition.x = x;
	ObjPosition.y = y;
}

float object::getSpeed()
{
	return speed;
}

float object::getX()
{
	return ObjPosition.x;
}

float object::getY()
{
	return ObjPosition.y;
}

void object::setSpeed(float s)
{
	speed = s;
}

std::string object::getState()
{
	return animState;
}

void object::setState(std::string st)
{
	animState = st;
}

glm::mat4 object::updateObject (bool additional)
{
	glutPostRedisplay();

	glm::mat4 TranslationMat = glm::translate(glm::mat4(), ObjPosition);
	const glm::vec3 worldRotationAxis_Z = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 rotationMat = glm::rotate(glm::mat4(), glm::radians(objRotationAngle), worldRotationAxis_Z);

	glm::mat4 scaleMat = glm::scale(glm::mat4(), objScale);

	glm::mat4 modelMat = TranslationMat * rotationMat * scaleMat;
	finalMat = cam1.project(modelMat);

	return finalMat;
}

void object::Render(int in)
{
	glUseProgram(Program_Object);


	gameManager::loadCurrentState(*this, Program_Object, in);

		
		


	glUniformMatrix4fv((glGetUniformLocation(Program_Object, "finalMat")), 1, GL_FALSE, glm::value_ptr(finalMat));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}




void object::imageLoader(std::string im, GLuint& TexNum)
{
	glGenTextures(1, &TexNum);
	int ImageWidth;
	int ImageHeight;
	int ImageComponents;


	std::string imageString = "Resources/Texture/" + im;


	unsigned char* ImageData = stbi_load(imageString.c_str(), &ImageWidth, &ImageHeight, &ImageComponents, 0);
	GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0, LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

//	textures.push_back(TexNum);
//	textures.push_back(TexNum);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(ImageData);

	glBindTexture(GL_TEXTURE_2D, TexNum);
	
}

void object::setStuff(glm::vec3 ObjPos, float objRotAngle, glm::vec3 objSc)
{
	ObjPosition = ObjPos;
	objRotationAngle = objRotAngle;
	objScale = objSc;
}
