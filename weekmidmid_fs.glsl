#version 430 core

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D u_tex;
uniform float u_time;
uniform int u_renderMode;

out vec4 FragColor;

void main()
{
    vec4 colorOnly = vec4(vColor, 1.0);

    if (u_renderMode == 1)
    {
        FragColor = colorOnly;
    }
    else if (u_renderMode == 2)
    {
        vec4 base = texture(u_tex, vTexCoord);
        vec4 edge = base * colorOnly;

        float t = 0.0;

        // 오른쪽 끝 10% 구간에서만 0 -> 1로 증가
        if (vTexCoord.x > 0.9)
            t = (vTexCoord.x - 0.9) / 0.1;

        if (t < 0.0) t = 0.0;
        if (t > 1.0) t = 1.0;

        FragColor = base * (1.0 - t) + edge * t;
    }
    else if (u_renderMode == 3)
    {
        vec2 uv = vTexCoord;
        uv.x += u_time * 0.15;   // 가로로 흐름
        FragColor = texture(u_tex, uv);
    }
    else
    {
        FragColor = texture(u_tex, vTexCoord);
    }
}