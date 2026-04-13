#version 430 core

in vec2 TexCoord;
in float vTime;

uniform sampler2D u_tex;

out vec4 FragColor;

void main()
{
    vec2 uv = TexCoord;

    // 물 텍스처를 움직이고 싶으면
    // 나중에 별도 uniform을 둬서 특정 오브젝트만 적용하는 게 더 좋다.
    // 지금은 예시라 그냥 아주 약하게만 둠.
    uv.x += vTime * 0.02;

    FragColor = texture(u_tex, uv);
}