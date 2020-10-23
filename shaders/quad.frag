#version 130


in vec2 outTexCoord;

out vec4 outColor;

uniform sampler2D frontCoords;
uniform sampler2D backCoords;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
	vec4 front = texture(frontCoords, outTexCoord);
	vec3 frontPos = front.xyz;
	vec4 back = texture(backCoords, outTexCoord);
	vec3 backPos = back.xyz;
	float d = map(distance(backPos, frontPos), 0, 0.5,  0, 1);
	outColor = vec4(frontPos, 1);
}