#include <sb7.h>
#include <vmath.h>
#include <shader.h>

// 실행하는 것만 주석해제
#define STB_IMAGE_IMPLEMENTATION

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
		stbi_set_flip_vertically_on_load(true);

		rendering_program = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLfloat vertices[] = {
			// 앞면
			0.25f,  0.25f,  0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 0
			-0.25f,  0.25f,  0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 1
			-0.25f, -0.25f,  0.25f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 2
			0.25f, -0.25f,  0.25f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // 3

			// 뒷면
			0.25f,  0.25f, -0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 4
			-0.25f,  0.25f, -0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 5
			-0.25f, -0.25f, -0.25f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 6
			0.25f, -0.25f, -0.25f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // 7

			// 왼쪽면
			-0.25f,  0.25f,  0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 8
			-0.25f,  0.25f, -0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 9
			-0.25f, -0.25f, -0.25f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 10
			-0.25f, -0.25f,  0.25f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // 11

			// 오른쪽면
			0.25f,  0.25f, -0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 12
			0.25f,  0.25f,  0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 13
			0.25f, -0.25f,  0.25f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 14
			0.25f, -0.25f, -0.25f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // 15

			// 윗면
			0.25f,  0.25f, -0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 16
			-0.25f,  0.25f, -0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 17
			-0.25f,  0.25f,  0.25f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 18
			0.25f,  0.25f,  0.25f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // 19

			// 아랫면
			0.25f, -0.25f,  0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 20
			-0.25f, -0.25f,  0.25f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 21
			-0.25f, -0.25f, -0.25f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 22
			0.25f, -0.25f, -0.25f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f    // 23
		};

		GLuint indices[] = {
			// 앞면 (z+)
			0, 1, 2,
			0, 2, 3,

			// 뒷면 (z-)
			4, 6, 5,
			4, 7, 6,

			// 왼쪽면 (x-)
			8, 9, 10,
			8, 10, 11,

			// 오른쪽면 (x+)
			12, 13, 14,
			12, 14, 15,

			// 윗면 (y+)
			16, 17, 18,
			16, 18, 19,

			// 아랫면 (y-)
			20, 21, 22,
			20, 22, 23
		};

		// VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 텍스처
		glGenTextures(6, textures);

		const char* filenames[6] = {
			"side1.jpg",
			"side2.jpg",
			"side3.jpg",
			"side4.jpg",
			"side5.jpg",
			"side6.jpg"
		};


		// 텍스처 이미지 로드
		for (int i = 0; i < 6; i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i]);

			int width, height, nrChannels;
			unsigned char* data = stbi_load(filenames[i], &width, &height, &nrChannels, 0);

			if (data) {
				GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			stbi_image_free(data); 

			// 텍스처 샘플링 / 필터링 설정
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		}

		

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
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// 6개 면 각각 그림
		for (int i = 0; i < 6; i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i]);

			// 각 면당 index 6개
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(GLuint)));
		}
	}

private:
	GLuint rendering_program;
	GLuint VAO, VBO, EBO;
	GLuint textures[6];
};

DECLARE_MAIN(my_application);

