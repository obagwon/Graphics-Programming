#include <sb7.h>
#include <vmath.h>
#include <shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Mesh
{
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLsizei indexCount = 0;
};

class my_application : public sb7::application
{
public:
    GLuint compile_shaders(void)
    {
        GLuint vertex_shader = sb7::shader::load("week7-4_vs.glsl", GL_VERTEX_SHADER);
        GLuint fragment_shader = sb7::shader::load("week7-4_fs.glsl", GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }

    Mesh createCube()
    {
        Mesh mesh;

        GLfloat vertices[] = {
            // position                // color               // texcoord

            // 앞
             0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
            -0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            -0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
             0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

            // 뒤
             0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
            -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
             0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

            // 좌
            -0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
            -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
            -0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

            // 우
            0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
            0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
            0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
             
            // top
             0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
            -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            -0.25f,  0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
             0.25f,  0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

            // bottom
             0.25f, -0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
            -0.25f, -0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
            -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
             0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f
        };

        GLuint indices[] = {
            0, 1, 2,   
            0, 2, 3,       // 앞

            4, 6, 5,   
            4, 7, 6,       // 뒤

            8, 9, 10,  
            8, 10, 11,     // 좌

            12, 13, 14, 
            12, 14, 15,   // 우

            16, 17, 18, 
            16, 18, 19,   // 위

            20, 21, 22, 
            20, 22, 23    // 아래
        };

        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // location 0 = 위치
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // location 1 = 색상
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // location 2 = 텍스처
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        mesh.indexCount = 36;
        return mesh;
    }

    Mesh createRoof()
    {
        Mesh mesh;

        GLfloat vertices[] = {
            // position                 // color                // texcoord

            // 앞
            0.0f,  0.5f,  0.0f,        1.0f, 0.0f, 0.0f,       0.5f, 1.0f,
            -0.25f,  0.25f,  0.25f,     1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
            0.25f, 0.25f,  0.25f,       1.0f, 0.0f, 0.0f,       1.0f, 0.0f,

            // 뒤
            0.0f,  0.5f,  0.0f,        1.0f, 1.0f, 0.0f,       0.5f, 1.0f,
            0.25f,  0.25f, -0.25f,      1.0f, 1.0f, 0.0f,       0.0f, 0.0f,
            -0.25f,  0.25f, -0.25f,     1.0f, 1.0f, 0.0f,       1.0f, 0.0f,

            // 좌
            0.0f,  0.5f,  0.0f,        0.0f, 1.0f, 0.0f,       0.5f, 1.0f,
            -0.25f,  0.25f, -0.25f,     0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
            -0.25f,  0.25f,  0.25f,     1.0f, 0.0f, 0.0f,       1.0f, 0.0f,

            // 우
            0.0f,  0.5f,  0.0f,        0.0f, 0.0f, 1.0f,       0.5f, 1.0f,
            0.25f, 0.25f,  0.25f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
            0.25f,  0.25f, -0.25f,      0.0f, 0.0f, 1.0f,       1.0f, 0.0f,
        };

        GLuint indices[] = {
            0, 1, 2,       // 앞

            3, 4, 5,       // 뒤

            6, 7, 8,      // 좌

            9, 10, 11,   // 우
        };

        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // location 0 = 위치
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // location 1 = 색상
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // location 2 = 텍스처
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        mesh.indexCount = 12;
        return mesh;
    }

    Mesh createFlag()
    {
        Mesh mesh;

        GLfloat vertices[] = {
            // position               // color              // texcoord
             0.0f,  0.075f, 0.0f,      0.6f, 0.9f, 1.5f,    0.0f, 1.0f,
             0.0f, -0.075f, 0.0f,      0.6f, 0.9f, 1.5f,    0.0f, 0.0f,
             0.5f,  0.00f, 0.0f,      0.6f, 0.9f, 1.5f,    1.0f, 0.5f
        };

        GLuint indices[] = {
            0, 1, 2
        };

        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // location 0 = 위치
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // location 1 = 색상
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // location 2 = 텍스처
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        mesh.indexCount = 3;
        return mesh;
    }

    Mesh createPlane()
    {
        Mesh mesh;

        GLfloat vertices[] = {
            // position                  // color               // texcoord
            -0.5f, 0.0f, -0.5f,          1.0f, 1.0f, 1.0f,     0.0f, 1.0f,  // 0
            -0.5f, 0.0f,  0.5f,          1.0f, 1.0f, 1.0f,     0.0f, 0.0f,  // 1
             0.5f, 0.0f,  0.5f,          1.0f, 1.0f, 1.0f,     1.0f, 0.0f,  // 2
             0.5f, 0.0f, -0.5f,          1.0f, 1.0f, 1.0f,     1.0f, 1.0f   // 3
             
            
        };

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        mesh.indexCount = 6;
        return mesh;
    }

    void drawMesh(const Mesh& mesh,
        GLuint tex,
        const vmath::mat4& model,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        double currentTime)
    {
        glUseProgram(rendering_program);

        glUniformMatrix4fv(loc_model, 1, GL_FALSE, model);
        glUniformMatrix4fv(loc_view, 1, GL_FALSE, view);
        glUniformMatrix4fv(loc_proj, 1, GL_FALSE, proj);
        glUniform1f(loc_time, (float)currentTime);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(loc_tex, 0);

        glBindVertexArray(mesh.vao);
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void drawCube(const vmath::vec3& position,
        const vmath::vec3& scaleValue,
        const vmath::vec4& rotation,
        GLuint tex,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        double currentTime)
    {
        vmath::mat4 model =
            vmath::translate(position) *
            vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
            vmath::scale(scaleValue);

        drawMesh(cubeMesh, tex, model, view, proj, currentTime);
    }

    void drawRoof(const vmath::vec3& position,
        const vmath::vec3& scaleValue,
        const vmath::vec4& rotation,
        GLuint tex,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        double currentTime)
    {
        vmath::mat4 model =
            vmath::translate(position) *
            vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
            vmath::scale(scaleValue);

        drawMesh(roofMesh, tex, model, view, proj, currentTime);
    }

    void drawHouse(const vmath::vec3& position,
        const vmath::vec3& scaleValue,
        const vmath::vec4& rotation,
        GLuint cubeTex,
        GLuint roofTex,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        double currentTime)
    {
        vmath::mat4 model =
            vmath::translate(position) *
            vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
            vmath::scale(scaleValue);

        drawMesh(cubeMesh, cubeTex, model, view, proj, currentTime);
        drawMesh(roofMesh, roofTex, model, view, proj, currentTime);
    }

    void drawFlag(const vmath::vec3& position,
        const vmath::vec3& scaleValue,
        const vmath::vec4& rotation,
        GLuint stickTex,
        GLuint flagTex,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        double currentTime)
    {
        // 깃발 전체 변환
        vmath::mat4 worldModel =
            vmath::translate(position) *
            vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
            vmath::scale(scaleValue);

        // 막대: 기본 큐브(0.5)를 x,z만 0.1배 해서 0.05로 만듦
        vmath::mat4 stickLocal =
            vmath::scale(0.1f, 1.0f, 0.1f);

        // 깃발: 막대 오른쪽으로 0.025, 위로 0.175 이동
        vmath::mat4 flagLocal =
            vmath::translate(0.025f, 0.175f, 0.0f);

        vmath::mat4 stickModel = worldModel * stickLocal;
        vmath::mat4 flagModel = worldModel * flagLocal;

        drawMesh(cubeMesh, stickTex, stickModel, view, proj, currentTime);
        drawMesh(flagMesh, flagTex, flagModel, view, proj, currentTime);
    }

    void drawPlane(const vmath::vec3& position,
        const vmath::vec3& scaleValue,
        const vmath::vec4& rotation,
        GLuint tex,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        double currentTime)
    {
        vmath::mat4 model =
            vmath::translate(position) *
            vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
            vmath::scale(scaleValue);

        drawMesh(planeMesh, tex, model, view, proj, currentTime);
    }

    GLuint loadTexture(const char* filename)
    {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

        if (data)
        {
            GLenum format = GL_RGB;
            if (nrChannels == 1) format = GL_RED;
            else if (nrChannels == 3) format = GL_RGB;
            else if (nrChannels == 4) format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        stbi_image_free(data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return tex;
    }

    virtual void startup() override
    {
        stbi_set_flip_vertically_on_load(true);

        rendering_program = compile_shaders();

        cubeMesh = createCube();
        roofMesh = createRoof();
        flagMesh = createFlag();
        planeMesh = createPlane();

        texture1 = loadTexture("side1.jpg");
        texture2 = loadTexture("side2.jpg");
        texture3 = loadTexture("side3.jpg");
        texture4 = loadTexture("side4.jpg");
        texture5 = loadTexture("side5.jpg");
        texture6 = loadTexture("container2.png");
        texSand = loadTexture("sand.jpg");
        texWater = loadTexture("water.jpg");

        loc_model = glGetUniformLocation(rendering_program, "u_model");
        loc_view = glGetUniformLocation(rendering_program, "u_view");
        loc_proj = glGetUniformLocation(rendering_program, "u_proj");
        loc_tex = glGetUniformLocation(rendering_program, "u_tex");
        loc_time = glGetUniformLocation(rendering_program, "u_time");
    }

    virtual void render(double currentTime) override
    {
        const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, black);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        vmath::vec3 eye(5.0f, 3.0f, 8.0f);
        vmath::vec3 center(0.0f, 0.0f, 0.0f);
        vmath::vec3 up(0.0f, 1.0f, 0.0f);

        vmath::mat4 view = vmath::lookat(eye, center, up);
        vmath::mat4 proj = vmath::perspective(
            50.0f,
            (float)info.windowWidth / (float)info.windowHeight,
            0.1f,
            1000.0f
        );

        // 큐브 여러 개와 집
        drawCube(vmath::vec3((float)sin(currentTime) * 2, 0.0f, (float)cos(currentTime) * 2),
            vmath::vec3(1.0f, 1.0f, 1.0f),
            vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
            texture1,
            view, proj, currentTime);

        drawCube(vmath::vec3(2.0f, 0.0f, 0.0f),
            vmath::vec3(1.5f, 1.0f, 1.0f),
            vmath::vec4((float)currentTime * 50.0f, 0.0f, 1.0f, 0.0f),
            texture2,
            view, proj, currentTime);

        drawCube(vmath::vec3(0.0f, 0.0f, 0.0f),
            vmath::vec3(0.8f, 2.0f, 0.8f),
            vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),
            texture3,
            view, proj, currentTime);

        drawCube(vmath::vec3(0.0f, 1.5f, 4.0f),
            vmath::vec3(2.0f, 2.0f, 2.0f),
            vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            texture4,
            view, proj, currentTime);

        drawCube(vmath::vec3(0.0f, 1.5f, -0.5f),
            vmath::vec3(1.0f, 2.0f, 0.5f),
            vmath::vec4((float)currentTime * 20.0f, 1.0f, 0.0f, 0.0f),
            texture5,
            view, proj, currentTime);

        drawHouse(vmath::vec3(0.0f, (float)sin(currentTime) * 2, (float)cos(currentTime) * 2),
            vmath::vec3(2.0f, 2.0f, 2.0f),
            vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
            texture6, texture1,
            view, proj, currentTime);

        drawFlag(vmath::vec3((float)sin(currentTime) * 2 -2.0f, 0.0f, (float)cos(currentTime) * 2),
            vmath::vec3(2.0f, 2.0f, 2.0f),
            vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
            texture6, texture1,
            view, proj, currentTime);

        drawPlane(vmath::vec3(0.0f, -0.3f, 0.0f),
            vmath::vec3(10.0f, 1.0f, 10.0f),
            vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
            texSand,
            view, proj, currentTime);
    }

    virtual void shutdown() override
    {
        glDeleteProgram(rendering_program);

        glDeleteTextures(1, &texture1);
        glDeleteTextures(1, &texture2);
        glDeleteTextures(1, &texture3);
        glDeleteTextures(1, &texture4);
        glDeleteTextures(1, &texture5);
        glDeleteTextures(1, &texture6);

        glDeleteVertexArrays(1, &cubeMesh.vao);
        glDeleteBuffers(1, &cubeMesh.vbo);
        glDeleteBuffers(1, &cubeMesh.ebo);

        glDeleteVertexArrays(1, &roofMesh.vao);
        glDeleteBuffers(1, &roofMesh.vbo);
        glDeleteBuffers(1, &roofMesh.ebo);

        glDeleteVertexArrays(1, &flagMesh.vao);
        glDeleteBuffers(1, &flagMesh.vbo);
        glDeleteBuffers(1, &flagMesh.ebo);

        glDeleteVertexArrays(1, &planeMesh.vao);
        glDeleteBuffers(1, &planeMesh.vbo);
        glDeleteBuffers(1, &planeMesh.ebo);
    }

private:
    GLuint rendering_program = 0;
    GLuint texture1 = 0;
    GLuint texture2 = 0;
    GLuint texture3 = 0;
    GLuint texture4 = 0;
    GLuint texture5 = 0;
    GLuint texture6 = 0;
    GLuint texSand = 0;
    GLuint texWater = 0;

    Mesh cubeMesh;
    Mesh roofMesh;
    Mesh flagMesh;
    Mesh planeMesh;

    GLint loc_model = -1;
    GLint loc_view = -1;
    GLint loc_proj = -1;
    GLint loc_tex = -1;
    GLint loc_time = -1;
};

DECLARE_MAIN(my_application)