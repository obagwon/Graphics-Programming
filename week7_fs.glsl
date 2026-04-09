#version 430 core

in vec3 vs_Color;
in vec2 vs_TexCoord;

uniform sampler2D texture1;

out vec4 fs_Color;

void main(void)
{
	//fs_Color = vec4(vs_Color, 1.0);   //vec4(vsColor.r, vsColor.g, vsColor.b, 1.0);
	fs_Color = texture(texture1, vs_TexCoord) * vec4(vs_Color, 1.0);
}