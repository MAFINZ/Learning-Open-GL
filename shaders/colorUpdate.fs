#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float inputColor;
uniform sampler2D ourTexture;
uniform int texOrNot;

void main()
{
	if(texOrNot == 1) {
		FragColor = vec4(texture(ourTexture, TexCoord).xyz, inputColor);
	} else if(texOrNot == 0) {	
		FragColor = vec4(1.0f, 0.5f, 0.2f, inputColor);
	}
}