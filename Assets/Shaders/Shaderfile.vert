#version 410 core

layout (row_major) uniform UniformData
{
	mat4 world;
	mat4 projection;
	int useColors;
};

layout(location = 0) in vec3 aposition;
layout(location = 2) in vec3 acolor;
layout(location = 1) in vec2 atexcoord;

//layout(location = 0) out vec3 vertOutColor;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	vec4 pos = vec4(aposition, 1) * world;
	pos = pos * projection;

	gl_Position = pos;

	//TexCoord = texcoord;

	//if (gl_Position.y>0 && gl_Position.y<1)
	//	gl_Position.x += 0.25;

	// vec3 has attributes x,y,z for rgb:
	//vertOutColor = vec3(color.x,color.y,color.z);

	ourColor = vec3(1.0,1.0,1.0);
	if (useColors == 1)
		ourColor = acolor;
	TexCoord = atexcoord;
}