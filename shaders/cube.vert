#version 130

in vec3 vs_in_pos;
in vec3 vs_in_col;

out vec3 vs_out_col;

uniform mat4 MVP;

void main()
{
	vec4 v = vec4( vs_in_pos, 1 );
	gl_Position = MVP * v;
	vs_out_col = gl_Position.xyz / gl_Position.w;
}