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

    if (u_renderMode == 0)
    {
        FragColor = texture(u_tex, vTexCoord);
    }
    else if (u_renderMode == 1)
    {
        FragColor = colorOnly;
    }
    else
    {
        FragColor = texture(u_tex, vTexCoord) * colorOnly;
    }
}