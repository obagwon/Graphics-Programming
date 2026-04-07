#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 rotMat;
uniform mat4 transMat;
uniform mat4 viewMat;
uniform mat4 perMat;

out vec3 vs_Color;

void main(void)
{
	gl_Position = perMat * viewMat * transMat * rotMat * vec4(pos.x, pos.y, pos.z, 1.0);

	vs_Color = color;
}
