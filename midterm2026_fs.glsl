#version 430 core

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D u_tex;
uniform float u_time;
uniform int u_renderMode;
uniform float alphaK;

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
        FragColor = texture(u_tex, vTexCoord) * colorOnly;
    }
    else if (u_renderMode == 3)
    {
        vec2 uv = vTexCoord;
        uv.y += u_time * 0.5;   
        FragColor = texture(u_tex, uv);
    }
    else if (u_renderMode == 4)
    {
        vec4 alpha = vec4(1.0, 1.0, 1.0, alphaK);
        FragColor = texture(u_tex, vTexCoord) * alpha;
    }
    else
    {
        FragColor = texture(u_tex, vTexCoord);
    }
}