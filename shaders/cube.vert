#version 130

in vec3 vs_in_pos;
in vec3 vs_in_col;

out vec3 vs_out_col;

uniform mat4 MVP;

uniform mat4 Rotation;

void main()
{
	vec4 v = vec4( vs_in_pos, 1 );
	gl_Position = MVP * v;
	vs_out_col = (Rotation * vec4(vs_in_pos, 1)).xyz;
}