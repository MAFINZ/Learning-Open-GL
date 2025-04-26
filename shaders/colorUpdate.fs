#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float inputColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int texOrNot;

void main()
{
	if(texOrNot == 1) {
		FragColor = vec4(mix(texture(texture1, TexCoord).xyz, texture(texture2, vec2(-TexCoord.x, TexCoord.y)).xyz, 0.2), inputColor);
	} else if(texOrNot == 0) {	
		FragColor = vec4(1.0f, 0.5f, 0.2f, inputColor);
	}
}