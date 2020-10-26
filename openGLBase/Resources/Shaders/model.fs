#version 460 core

in vec2 fragTexCoords;

uniform sampler2D texture_diffuse1;

out vec4 color;

void main()
{
    color  = texture(texture_diffuse1, fragTexCoords);
}