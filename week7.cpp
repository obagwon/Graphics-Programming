#include <sb7.h>
#include <vmath.h>
#include <shader.h>

// 실행하는 것만 주석해제
//#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

class my_application : public sb7::application {
public:
	// 컴파일 쉐이더
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		vertex_shader = sb7::shader::load("week7_vs.glsl", GL_VERTEX_SHADER);

		fragment_shader = sb7::shader::load("week7_fs.glsl", GL_FRAGMENT_SHADER);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}


	virtual void startup() {
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLfloat vertices[] = {
			// 앞
			0.25f, 0.25f, 0.25f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// 0
			-0.25f, 0.25f, 0.25f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		// 1
			-0.25f, -0.25f, 0.25f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		// 2
			0.25f, -0.25f, 0.25f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,		// 3

			// 뒤
			0.25f, 0.25f, -0.25f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,		// 4
			-0.25f, 0.25f, -0.25f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,		// 5
			-0.25f, -0.25f, -0.25f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// 6
			0.25f, -0.25f, -0.25f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f		// 7
		};

		GLuint indices[] = {
			0, 1, 2,	// 앞
			0, 2, 3,

			5, 4, 7,	// 뒤
			5, 7, 6,

			1, 5, 6,	// 좌
			1, 6, 2,

			4, 0, 3,	// 우
			4, 3, 7,

			4, 5, 1,	// 위
			4, 1, 0,

			3, 2, 6,	// 아래
			3, 6, 7
		};

		// VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 텍스처
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// 텍스처 이미지 로드
		int width, height, nrChannels;
		unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);

		// 텍스처 샘플링 / 필터링 설정
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		
		// 위치 = 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// 색상 = 1
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 텍스처 좌표 = 2
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); 
		glEnableVertexAttribArray(2);

		// EBO
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	virtual void shutdown() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
	}

	virtual void render(double currentTime) {
		const GLfloat black[] = { 0.0,
								0.0,
								0.0,
								1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		glEnable(GL_CULL_FACE);

		glUseProgram(rendering_program);
		float angle = currentTime * 50;

		// 회전
		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 1.0f, 0.0f);
		GLuint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);

		// 이동
		vmath::mat4 tm = vmath::translate((float)sin(currentTime) * 2, 0.0f, (float)cos(currentTime) * 2);
		GLuint transMatLocation = glGetUniformLocation(rendering_program, "transMat");
		glUniformMatrix4fv(transMatLocation, 1, GL_FALSE, tm);

		// 뷰
		vmath::vec3 eye(5.0, 2.0, 3.0);
		vmath::vec3 center(0.0, 0.0, 0.0);
		vmath::vec3 up(0.0, 1.0, 0.0);
		vmath::mat4 vm = vmath::lookat(eye, center, up);
		GLuint viewMatLocation = glGetUniformLocation(rendering_program, "viewMat");
		glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, vm);

		// 프로젝션
		vmath::mat4 pm = vmath::perspective(50.0f, info.windowWidth / info.windowHeight, 0.1f, 1000.0f);
		GLuint perMatLocation = glGetUniformLocation(rendering_program, "perMat");
		glUniformMatrix4fv(perMatLocation, 1, GL_FALSE, pm);

		// 텍스처 바인드
		glUniform1i(glGetUniformLocation(rendering_program, "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

private:
	GLuint rendering_program;
	GLuint VAO, VBO, EBO;
	GLuint texture;
};

//DECLARE_MAIN(my_application);

