#version 460 core

in vec3 FragColor;
//uniform float CurrentTime;
in vec2 FragTexCoords;
uniform sampler2D ImageTexture;
uniform sampler2D ImageTexture2;
uniform sampler2D ImageAnim;
uniform float deltaTime;

out vec4 FinalColor;
vec2 FragTex = FragTexCoords;
void main()
{
   
    FragTex.y += 0.0001f * deltaTime;
    if(FragTex.y == 1.0f)
        FragTex.y = 0.0f;
    FinalColor = texture(ImageTexture,FragTex);
}