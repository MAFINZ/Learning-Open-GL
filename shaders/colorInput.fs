#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform float alphaColor;

void main()
{
	FragColor = vec4(ourColor, alphaColor);
}