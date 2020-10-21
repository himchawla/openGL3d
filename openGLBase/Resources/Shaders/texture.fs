#version 460 core

in vec3 FragColor;
//uniform float CurrentTime;
in vec2 FragTexCoords;
uniform sampler2D textures;
uniform sampler2D ImageTexture2;
uniform sampler2D ImageAnim;
uniform float scale;

out vec4 FinalColor;

void main()
{
    FinalColor  = texture(textures, FragTexCoords);
}