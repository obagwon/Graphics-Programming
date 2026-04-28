#version 430 core

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vPos;

uniform sampler2D u_tex;
uniform float u_time;
uniform int u_renderMode;
uniform float alphaK;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

out vec4 FragColor;


void main()
{
    vec4 colorOnly = vec4(vColor, 1.0);

    if (u_renderMode == 1) // 색상만
    {
        FragColor = colorOnly;
    }
    else if (u_renderMode == 2) // 텍스처 * 색상
    {
        FragColor = texture(u_tex, vTexCoord) * colorOnly;
    }
    else if (u_renderMode == 3) // 움직이는 텍스처
    {
        vec2 uv = vTexCoord;
        uv.y += u_time * 0.5;   
        FragColor = texture(u_tex, uv);
    }
    else if (u_renderMode == 4) // 투명도 적용된 텍스처
    {
        vec4 alpha = vec4(1.0, 1.0, 1.0, alphaK);
        FragColor = texture(u_tex, vTexCoord) * alpha;
    }
    else if (u_renderMode == 5) // 라이팅
    {
        float ambientStrength = 0.1; 
        vec3 ambient = ambientStrength * lightColor; 

        vec3 norm = normalize(vNormal); 
        vec3 lightDir = normalize(lightPos - vPos); 
        float diff = max(dot(norm, lightDir), 0.0); 
        vec3 diffuse = diff * lightColor;

        vec3 viewDir = normalize(viewPos - vPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float specularStrength = 0.5;
        int shininess = 32;
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
        vec3 specular = specularStrength * spec * lightColor;

        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
    else // 텍스처만
    {
        FragColor = texture(u_tex, vTexCoord);
    }
}

