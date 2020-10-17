#version 130

in vec3 position;
in vec2 texCoord;

out vec2 outTexCoord;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4( position, 1 );
	outTexCoord = texCoord;
}
