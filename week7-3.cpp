#include <sb7.h>
#include <vmath.h>
#include <shader.h>

//#define STB_IMAGE_IMPLEMENTATION
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
    GLuint program = 0;

    Mesh cubeMesh;
    Mesh planeMesh;

    GLuint texSand = 0;
    GLuint texWater = 0;
    GLuint texWall = 0;

    GLint loc_model = -1;
    GLint loc_view = -1;
    GLint loc_proj = -1;
    GLint loc_tex = -1;
    GLint loc_time = -1;

    // -----------------------------
    // 셰이더 컴파일
    // -----------------------------
    GLuint compile_shaders()
    {
        GLuint vs = sb7::shader::load("week7-3_vs.glsl", GL_VERTEX_SHADER);
        GLuint fs = sb7::shader::load("week7-3_fs.glsl", GL_FRAGMENT_SHADER);

        GLuint prog = glCreateProgram();
        glAttachShader(prog, vs);
        glAttachShader(prog, fs);
        glLinkProgram(prog);

        GLint success = 0;
        glGetProgramiv(prog, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar log[1024];
            glGetProgramInfoLog(prog, 1024, nullptr, log);
            OutputDebugStringA(log);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        return prog;
    }

    // -----------------------------
    // 텍스처 로드
    // -----------------------------
    GLuint load_texture(const char* filename, bool flip = true)
    {
        if (flip)
            stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
        if (!data)
        {
            OutputDebugStringA("Texture load failed.\n");
            return 0;
        }

        GLenum format = GL_RGB;
        if (channels == 1) format = GL_RED;
        else if (channels == 3) format = GL_RGB;
        else if (channels == 4) format = GL_RGBA;

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        return tex;
    }

    // -----------------------------
    // plane 생성 (EBO 사용)
    // xz 평면 위에 놓임
    // -----------------------------
    Mesh create_plane()
    {
        Mesh mesh;

        float vertices[] =
        {
            // position               // texcoord
            -0.5f, 0.0f, -0.5f,       0.0f, 0.0f,
             0.5f, 0.0f, -0.5f,       1.0f, 0.0f,
             0.5f, 0.0f,  0.5f,       1.0f, 1.0f,
            -0.5f, 0.0f,  0.5f,       0.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };

        glGenVertexArrays(1, &mesh.vao);
        glGenBuffers(1, &mesh.vbo);
        glGenBuffers(1, &mesh.ebo);

        glBindVertexArray(mesh.vao);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        mesh.indexCount = 6;
        return mesh;
    }

    // -----------------------------
    // cube 생성 (면마다 uv가 필요해서 정점 24개)
    // EBO 사용
    // -----------------------------
    Mesh create_cube()
    {
        Mesh mesh;

        float vertices[] =
        {
            // front
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

            // back
             0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

             // left
             -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
             -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
             -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

             // right
              0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
              0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
              0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

              // top
              -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
               0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
               0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
              -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

              // bottom
              -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
               0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
               0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
              -0.5f, -0.5f,  0.5f,   0.0f, 1.0f
        };

        unsigned int indices[] =
        {
             0,  1,  2,   0,  2,  3,   // front
             4,  5,  6,   4,  6,  7,   // back
             8,  9, 10,   8, 10, 11,   // left
            12, 13, 14,  12, 14, 15,   // right
            16, 17, 18,  16, 18, 19,   // top
            20, 21, 22,  20, 22, 23    // bottom
        };

        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
                

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        mesh.indexCount = 36;
        return mesh;
    }

    // -----------------------------
    // 공용 draw 함수
    // -----------------------------
    void drawMesh(const Mesh& mesh,
        GLuint texture,
        const vmath::mat4& model,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime,
        bool animateWater = false)
    {
        glUseProgram(program);

        glUniformMatrix4fv(loc_model, 1, GL_FALSE, model);
        glUniformMatrix4fv(loc_view, 1, GL_FALSE, view);
        glUniformMatrix4fv(loc_proj, 1, GL_FALSE, proj);
        glUniform1f(loc_time, currentTime);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(loc_tex, 0);

        // 물 흐름 여부를 다른 uniform으로 분기해도 되지만
        // 여기서는 간단히 time 값 활용용으로만 둔다.
        glBindVertexArray(mesh.vao);
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void drawCube(GLuint texture,
        const vmath::mat4& model,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime)
    {
        drawMesh(cubeMesh, texture, model, view, proj, currentTime);
    }

    void drawPlane(GLuint texture,
        const vmath::mat4& model,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime)
    {
        drawMesh(planeMesh, texture, model, view, proj, currentTime);
    }

    // -----------------------------
    // 장면용 함수들
    // -----------------------------
    void drawGround(const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime)
    {
        vmath::mat4 model =
            vmath::translate(0.0f, -1.0f, 0.0f) *
            vmath::scale(18.0f, 1.0f, 18.0f);

        drawPlane(texSand, model, view, proj, currentTime);
    }

    void drawRiver(const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime)
    {
        // 강을 plane 3개로 이어붙여 굽은 느낌 내기
        vmath::mat4 m1 =
            vmath::translate(-2.5f, -0.95f, 4.0f) *
            vmath::rotate(15.0f, 0.0f, 1.0f, 0.0f) *
            vmath::scale(3.0f, 1.0f, 6.0f);

        vmath::mat4 m2 =
            vmath::translate(0.0f, -0.95f, 0.0f) *
            vmath::rotate(28.0f, 0.0f, 1.0f, 0.0f) *
            vmath::scale(3.2f, 1.0f, 6.5f);

        vmath::mat4 m3 =
            vmath::translate(2.5f, -0.95f, -4.0f) *
            vmath::rotate(42.0f, 0.0f, 1.0f, 0.0f) *
            vmath::scale(3.0f, 1.0f, 6.0f);

        drawPlane(texWater, m1, view, proj, currentTime);
        drawPlane(texWater, m2, view, proj, currentTime);
        drawPlane(texWater, m3, view, proj, currentTime);
    }

    void drawWall(const vmath::vec3& pos,
        const vmath::vec3& scaleValue,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime)
    {
        vmath::mat4 model =
            vmath::translate(pos) *
            vmath::scale(scaleValue);

        drawCube(texWall, model, view, proj, currentTime);
    }

    void drawHouse(const vmath::vec3& pos,
        const vmath::vec3& bodyScale,
        const vmath::mat4& view,
        const vmath::mat4& proj,
        float currentTime)
    {
        // 집 몸체
        vmath::mat4 bodyModel =
            vmath::translate(pos) *
            vmath::scale(bodyScale);

        drawCube(texWall, bodyModel, view, proj, currentTime);

        // 지붕을 일단 납작한 cube로 단순화
        vmath::mat4 roofModel =
            vmath::translate(pos[0], pos[1] + bodyScale[1] * 0.65f, pos[2]) *
            vmath::scale(bodyScale[0] * 1.1f, bodyScale[1] * 0.25f, bodyScale[2] * 1.1f);

        drawCube(texSand, roofModel, view, proj, currentTime);
    }

    // -----------------------------
    // 초기화
    // -----------------------------
    void startup()
    {
        program = compile_shaders();

        cubeMesh = create_cube();
        planeMesh = create_plane();

        texSand = load_texture("sand.jpg");
        texWater = load_texture("water.jpg");
        texWall = load_texture("wall.jpg");

        loc_model = glGetUniformLocation(program, "u_model");
        loc_view = glGetUniformLocation(program, "u_view");
        loc_proj = glGetUniformLocation(program, "u_proj");
        loc_tex = glGetUniformLocation(program, "u_tex");
        loc_time = glGetUniformLocation(program, "u_time");

        glEnable(GL_DEPTH_TEST);
    }

    void shutdown()
    {
        glDeleteProgram(program);

        glDeleteTextures(1, &texSand);
        glDeleteTextures(1, &texWater);
        glDeleteTextures(1, &texWall);

        glDeleteVertexArrays(1, &cubeMesh.vao);
        glDeleteBuffers(1, &cubeMesh.vbo);
        glDeleteBuffers(1, &cubeMesh.ebo);

        glDeleteVertexArrays(1, &planeMesh.vao);
        glDeleteBuffers(1, &planeMesh.vbo);
        glDeleteBuffers(1, &planeMesh.ebo);
    }

    // -----------------------------
    // 렌더
    // -----------------------------
    void render(double currentTime)
    {
        static const GLfloat gray[] = { 0.70f, 0.85f, 0.95f, 1.0f };
        static const GLfloat one = 1.0f;

        glClearBufferfv(GL_COLOR, 0, gray);
        glClearBufferfv(GL_DEPTH, 0, &one);

        float t = (float)currentTime;

        // 자동 카메라
        vmath::vec3 eye(
            sinf(t * 0.25f) * 10.0f,
            5.5f,
            cosf(t * 0.25f) * 10.0f
        );

        vmath::mat4 view = vmath::lookat(
            eye,
            vmath::vec3(0.0f, 0.0f, 0.0f),
            vmath::vec3(0.0f, 1.0f, 0.0f)
        );

        vmath::mat4 proj = vmath::perspective(
            50.0f,
            (float)info.windowWidth / (float)info.windowHeight,
            0.1f,
            100.0f
        );

        drawGround(view, proj, t);
        drawRiver(view, proj, t);

        // 벽
        drawWall(vmath::vec3(-7.0f, 1.5f, -6.0f), vmath::vec3(1.5f, 3.0f, 2.0f), view, proj, t);
        drawWall(vmath::vec3(7.0f, 1.5f, 6.0f), vmath::vec3(1.5f, 3.0f, 2.0f), view, proj, t);

        // 집들
        drawHouse(vmath::vec3(-4.0f, 0.0f, 1.5f), vmath::vec3(1.6f, 1.6f, 1.6f), view, proj, t);
        drawHouse(vmath::vec3(4.5f, 0.0f, -2.0f), vmath::vec3(1.8f, 2.0f, 1.8f), view, proj, t);
        drawHouse(vmath::vec3(-7.0f, 0.0f, 6.0f), vmath::vec3(2.0f, 2.2f, 2.0f), view, proj, t);
    }
    
};

//DECLARE_MAIN(my_application)