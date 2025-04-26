#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = vec4(mix(texture(texture1, TexCoord).xyz, texture(texture2, vec2(-TexCoord.x, TexCoord.y)).xyz, 0.2), 1.0f);
	
}