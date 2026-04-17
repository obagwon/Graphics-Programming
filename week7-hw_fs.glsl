#version 430 core

in vec3 vs_Color;
in vec2 vs_TexCoord;

uniform sampler2D texture1; // 숫자
uniform sampler2D texture2; // 배경

out vec4 fs_Color;

void main(void)
{
    vec4 num = texture(texture1, vs_TexCoord);
    vec4 bg  = texture(texture2, vs_TexCoord);

    float brightness = (num.r + num.g + num.b) / 3.0;

    if (brightness > 0.96)
        fs_Color = bg;
    else
        fs_Color = num;
}