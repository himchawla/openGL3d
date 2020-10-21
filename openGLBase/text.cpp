
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: text.cpp
// Description	: Text Rendering
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Local Includes


#include "text.h"


GLuint indices[] =
{
	0,1,2,
	0,2,3,
};

void text::Release()
{
	FT_Done_Face(Face);
	FT_Done_FreeType(Library);
}

void text::genBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	InitializedCorrectly = true;
}

GLuint text::GenerateTexture(FT_Face *face)
{
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		(*face)->glyph->bitmap.width,
		(*face)->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		(*face)->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return TextureID;

}
void text::Update()
{

}
void text::loadChars(std::string Font)
{
	ProjectionMat = glm::ortho(0.0f, (float)1000.0f, 0.0f, 1000.0f);
	Program_Text = ShaderLoader::CreateProgram("Resources/Shaders/text.vs", "Resources/Shaders/text.fs");

	if (FT_Init_FreeType(&Library) != FT_Err_Ok)
		std::cout << "Error Fretypr initialisiing failed" << std::endl;
	return;

	if ((FT_New_Face(Library, Font.c_str(), 0, &Face) != FT_Err_Ok))
	{
		std::cout << "Error::FREETYPE: Failed to load font - " << Font << std::endl;

	}
	FT_Set_Pixel_Sizes(Face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte CharIndex = 0; CharIndex < FontCharacterLimit; CharIndex++)
	{
		if (FT_Load_Char(Face, CharIndex, FT_LOAD_RENDER) != FT_Err_Ok)
		{
			std::cout << "ERROR::FREETYPE: Failed to load ascii index - " << CharIndex << std::endl;
			continue;
		}

		FontCharacters[CharIndex] = {
			GenerateTexture(&Face),
		glm::ivec2(Face->glyph->bitmap.width, Face->glyph->bitmap.rows),
			glm::ivec2(Face->glyph->bitmap_left, Face->glyph->bitmap_top),
			(GLuint)Face->glyph->advance.x >> 6,
		};
	}
}


void text::Render()
{
	if (InitializedCorrectly == false)
	{
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(Program_Text);
	glUniform3fv(glGetUniformLocation(Program_Text, "TextColor"), 1, glm::value_ptr(Color));
	glUniformMatrix4fv(glGetUniformLocation(Program_Text, "ProjectionMat"), 1, GL_FALSE, glm::value_ptr(ProjectionMat));

	glBindVertexArray(VAO);

	glm::vec2 LocalPosition = Position;

	for (std::string::const_iterator CharIter = TextStr.begin(); CharIter!=TextStr.end();CharIter++)
	{
		FontCharacter FontChar = FontCharacters[*CharIter];
		GLfloat XPos = LocalPosition.x + (FontChar.Bearing.x * Scale.x);
		GLfloat YPos = LocalPosition.y - (FontChar.Size.y - FontChar.Bearing.y) * Scale.y;
		GLfloat Width = FontChar.Size.x * Scale.x;
		GLfloat Height = FontChar.Size.y * Scale.y;

		GLfloat Vertices[4][4] = {
			{XPos, YPos + Height, 0.0f,0.0f},
			{XPos, YPos, 0.0f,0.0f},
			{XPos + Width, YPos, 0.0f,0.0f},
			{XPos + Width, YPos + Height, 0.0f,0.0f},
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);

		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, FontChar.TextureID);
		glUniform1i(glGetUniformLocation(Program_Text, "TextTexture"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		LocalPosition.x += FontChar.Advance * Scale.x;

		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glDisable(GL_BLEND);
	}

}

