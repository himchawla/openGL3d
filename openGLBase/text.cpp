
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

	for (std::string::const_iterator CharIter = TextStr.begin(); CharIter != TextStr.end(); CharIter++)
	{
		FontCharacter FontChar = FontCharacters[*CharIter];
		GLfloat XPos = LocalPosition.x + (FontChar.Bearing.x * Scale.x);
		GLfloat YPos = LocalPosition.y - (FontChar.Size.y - FontChar.Bearing.y) * Scale.y;
		GLfloat Width = FontChar.Size.x * Scale.x;
		GLfloat Height = FontChar.Size.y * Scale.y;

		GLfloat Vertices[4][4] = {
			{XPos, YPos + Height, 0.0f,0.0f},
			{XPos, YPos, 0.0f,1.0f},
			{XPos + Width, YPos, 1.0f,1.0f},
			{XPos + Width, YPos + Height, 1.0f,0.0f},
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FontChar.TextureID);
		glUniform1i(glGetUniformLocation(Program_Text, "TextTexture"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		LocalPosition.x += FontChar.Advance * Scale.x;
	}
		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);


		glDisable(GL_BLEND);
	

}

