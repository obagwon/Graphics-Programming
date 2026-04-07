#include <sb7.h>
#include <vmath.h>
#include <shader.h>

class my_application : public sb7::application {
public:
	// 컴파일 쉐이더
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

	// 컴파일 쉐이더 2
	GLuint compile_shaders2(void) {
		GLuint vertex_shader2;
		GLuint fragment_shader2;
		GLuint program2;

		const GLchar* fragment_shader_source2[] =
		{
			"#version 430 core							\n"
			"											\n"
			"in vec4 vs_color;							\n"
			"											\n"
			"out vec4 color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	color = vs_color;						\n"
			"}											\n"
		};

		vertex_shader2 = sb7::shader::load("bar_vs_5.glsl", GL_VERTEX_SHADER);

		fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader2, 1, fragment_shader_source2, NULL);
		glCompileShader(fragment_shader2);

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
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

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

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 위치
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		// 색상
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	virtual void shutdown() {
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
		glDeleteProgram(rendering_program2);
	}

	virtual void render(double currentTime) {
		const GLfloat black[] = { 0.0,
								0.0,
								0.0,
								1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		glUseProgram(rendering_program2);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		
		glUseProgram(rendering_program);
		float angle = currentTime * 50;
		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 0.0f, 1.0f);
		GLuint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);
		glBindVertexArray(vertex_array_object);
		glDrawArrays(GL_TRIANGLES, 0, 12);

	}

private:
	GLuint rendering_program;
	GLuint rendering_program2;
	GLuint vertex_array_object;
};

DECLARE_MAIN(my_application);

