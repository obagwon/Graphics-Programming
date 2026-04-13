#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform float u_time;

out vec2 TexCoord;
out float vTime;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(aPos, 1.0);
    TexCoord = aTex;
    vTime = u_time;
}