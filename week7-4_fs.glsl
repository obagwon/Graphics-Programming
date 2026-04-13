#version 430 core

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D u_tex;
uniform float u_time;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(u_tex, vTexCoord);
    //FragColor = texColor * vec4(vColor, 1.0);
    FragColor = texColor;
}