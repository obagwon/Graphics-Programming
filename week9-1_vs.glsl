#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 vColor;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vPos;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(aPos, 1.0);
    vPos = vec3(u_model * vec4(aPos, 1.0));
    vNormal =  mat3(transpose(inverse(u_model))) * aNormal;
    vColor = aColor;
    vTexCoord = aTexCoord;
}