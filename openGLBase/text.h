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

	//	GLuint Program_Text;

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
	GLuint Program_Text = 0;
	FontCharacter FontCharacters[FontCharacterLimit];
public:


	void Update();


	text(std::string TextStr,
		std::string Font,
		glm::vec2 PixelSize,
		glm::vec2 Position,
		glm::vec3 Color = glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec2 Scale = glm::vec2(1.0f, 1.0f))
	{
		//Program_Text = ShaderLoader::CreateProgram("Resources/Shaders/text.vs", "Resources/Shaders/text.fs");
		SetText(TextStr);
		SetPosition(Position);
		SetColor(Color);
		SetScale(Scale);

		ProjectionMat = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);
		Program_Text = ShaderLoader::CreateProgram("Resources/Shaders/text.vs", "Resources/Shaders/text.fs");



		FT_Library Library;
		FT_Face Face;


		if (FT_Init_FreeType(&Library) != FT_Err_Ok)
		{
			std::cout << "ERROR::FREETYPE: Could not initialize Freetype Library" << std::endl;
			return;
		}

		if (FT_New_Face(Library, Font.c_str(), 0, &Face) != FT_Err_Ok)
		{
			std::cout << "ERROR::FREETYPE: Failed to load Font - " << Font << std::endl;
			return;
		}

		FT_Set_Pixel_Sizes(Face, (FT_UInt)PixelSize.x, (FT_UInt)PixelSize.y);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (GLubyte CharIndex = 0; CharIndex < FontCharacterLimit; CharIndex++)
		{
			if (FT_Load_Char(Face, CharIndex, FT_LOAD_RENDER) != FT_Err_Ok)
			{
				std::cout << "ERROR::FREETYPE: Failed to load Glyph Ascii Index - " << CharIndex << std::endl;
				continue;
			}

			FontCharacters[CharIndex] = {
				GenerateTexture(&Face),
				glm::ivec2(Face->glyph->bitmap.width, Face->glyph->bitmap.rows),
				glm::ivec2(Face->glyph->bitmap_left, Face->glyph->bitmap_top),
				(GLuint)Face->glyph->advance.x >> 6
			};
		}

		FT_Done_Face(Face);
		FT_Done_FreeType(Library);

		GLuint Indices[] = {
			0,1,2,
			0,2,3,
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint EBO;
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);


		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		InitializedCorrectly = true;

	}
	void Release();

	void genBuffers();





	~text() {};
	void Render();
	void SetColor(glm::vec3 Color) { this->Color = Color; }
	void SetPosition(glm::vec2 Postion) { this->Position = Postion; }
	void SetScale(glm::vec2 Scale) { this->Scale = Scale; }
	void SetText(std::string Text) { this->TextStr = Text; }

	void loadChars(std::string Font);
};
