#version 130


in vec2 outTexCoord;

out vec4 outColor;

uniform sampler2D texImage;

void main()
{
	outColor = vec4(texture(texImage, outTexCoord).xyz, 1);
}