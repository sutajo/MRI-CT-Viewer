#version 130

in vec2 outTexCoord;

out vec4 outColor;

uniform sampler2D texImage;

void main()
{
	vec4 tex = texture(texImage, outTexCoord);
	outColor = vec4(tex.xyz, 1);
}