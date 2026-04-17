#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(aPos, 1.0);
    vColor = aColor;
    vTexCoord = aTexCoord;
}