#pragma once
#include<glew.h>
#include<freeglut.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<ft2build.h>
#include FT_FREETYPE_H

#include<string>
#include<iostream>

#include"ShaderLoader.h"




class text
{
private:
	
	struct FontCharacter
	{
		GLuint TextureID = 0;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance = 0;
	};

	GLuint Program_Text;
	
	GLuint GenerateTexture(FT_Face* Face);

	static const int FontCharacterLimit = 128;
	bool InitializedCorrectly = false;

	std::string TextStr;
	glm::vec2 Position;
	glm::vec2 Scale;
	glm::vec3 Color;

	glm::mat4 ProjectionMat;
	GLuint VAO = 0;
	GLuint VBO = 0;
	//GLuint Program_Text = 0;
	FontCharacter FontCharacters[FontCharacterLimit];
public:

	
	void Update();
	text(std::string TextStr,
		std::string Font,
		glm::vec2 PixelSize,
		glm::vec2 Position,
		glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2 Scale = glm::vec2(1.0f, 1.0f))
	{
		//Program_Text = ShaderLoader::CreateProgram("Resources/Shaders/text.vs", "Resources/Shaders/text.fs");
		SetText(TextStr);
		SetPosition(Position);
		SetColor(Color);
		SetScale(Scale);

		

	}
	
		FT_Library Library;
		FT_Face Face;

		
		void Release();

		void genBuffers();

		

		text() { Face = 0;
		Library = 0;
		Program_Text = 0;
		};

	~text() {};
	void Render();
	void SetColor(glm::vec3 Color) { this->Color = Color; }
	void SetPosition(glm::vec2 Postion) { this->Position = Position; }
	void SetScale(glm::vec2 Scale) { this->Scale = Scale; }
	void SetText(std::string Text) { this->TextStr = Text; }

	void loadChars(std::string Font);
};

