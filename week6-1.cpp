#include <sb7.h>
#include <vmath.h>
#include <shader.h>

class my_application : public sb7::application {
public:
	// 컴파일 쉐이더 (바람개비)
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		vertex_shader = sb7::shader::load("week6_vs.glsl", GL_VERTEX_SHADER);

		fragment_shader = sb7::shader::load("week6_fs.glsl", GL_FRAGMENT_SHADER);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	// 컴파일 쉐이더 2 (막대)
	GLuint compile_shaders2(void) {
		GLuint vertex_shader2;
		GLuint fragment_shader2;
		GLuint program2;

		vertex_shader2 = sb7::shader::load("week6_vs2.glsl", GL_VERTEX_SHADER);

		fragment_shader2 = sb7::shader::load("week6_fs2.glsl", GL_FRAGMENT_SHADER);

		program2 = glCreateProgram();
		glAttachShader(program2, vertex_shader2);
		glAttachShader(program2, fragment_shader2);
		glLinkProgram(program2);

		glDeleteShader(vertex_shader2);
		glDeleteShader(fragment_shader2);

		return program2;
	}

	virtual void startup() {
		rendering_program = compile_shaders();
		rendering_program2 = compile_shaders2();
		glGenVertexArrays(2, VAOs);

		// 바람개비
		GLfloat vertices[] = {
			0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.25f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
			0.25f, 0.25f, 0.5f, 0.0f, 0.0f, 1.0f,

			0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.25f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.25f, 0.25f, 0.5f, 0.0f, 0.0f, 1.0f,

			0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			-0.25f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, 0.5f, 0.0f, 0.0f, 1.0f,

			0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.0f, -0.25f, 0.5f, 0.0f, 1.0f, 0.0f,
			0.25f, -0.25f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		// 막대
		GLfloat vertices2[] = {
			-0.01f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
			-0.01f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f,
			0.01f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f,

			-0.01f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
			0.01f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f,
			0.01f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f
		};

		glGenBuffers(2, VBOs);

		// 바람개비
		glBindVertexArray(VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 바람개비 위치
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// 바람개비 색상
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 막대
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		// 막대 위치
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// 막대 색상
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	virtual void shutdown() {
		glDeleteVertexArrays(1, VAOs);
		glDeleteProgram(rendering_program);
		glDeleteProgram(rendering_program2);
	}

	virtual void render(double currentTime) {
		const GLfloat black[] = { 0.0,
								0.0,
								0.0,
								1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		// 막대
		glUseProgram(rendering_program2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 바람개비
		glUseProgram(rendering_program);
		float angle = currentTime * 50;
		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 0.0f, 1.0f);
		GLuint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 12);

	}

private:
	GLuint rendering_program;
	GLuint rendering_program2;
	GLuint VAOs[2];
	GLuint VBOs[2];
};

DECLARE_MAIN(my_application);

