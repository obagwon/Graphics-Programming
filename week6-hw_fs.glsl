#version 430 core

in vec3 vs_Color;
out vec4 fs_Color;

void main(void)
{
	fs_Color = vec4(vs_Color, 1.0);   //vec4(vsColor.r, vsColor.g, vsColor.b, 1.0);
}