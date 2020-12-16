#version 130


in vec2 outTexCoord;

out vec4 outColor;

uniform sampler2D texImage;
uniform sampler2D backTexture;
uniform sampler3D volume;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

int maxIterations = 2000;
float threshold = 0.2;
float step = 0.005;

void main()
{
	vec4 front = texture(texImage, outTexCoord);
	vec4 back = texture(backTexture, outTexCoord);
	vec3 frontPos = front.xyz;
	vec3 backPos = back.xyz;
	int iteration = 0;
    bool go = true;
	vec3 p = frontPos;
	vec3 v = backPos - frontPos;
	vec4 volume_data;
	if(v != 0)
	{
		v = normalize(v);
		while(iteration < maxIterations && go)
		{
			volume_data = texture(volume, p);
			go = volume_data.x < threshold;
			p = p + step*v;
			iteration++;
		}
	}
	
	if(iteration < maxIterations && v!=0){
		float d = map(iteration, 0, maxIterations, 0, 1);
		outColor = vec4(d,d,d,1);
	}
    else
		outColor = vec4(0,0,0,1);
	

	//outColor = vec4(volume_data.xyz, 1);
}