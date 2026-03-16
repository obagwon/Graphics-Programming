#include <sb7.h>
#include<vmath.h>

class my_application : public sb7::application {
public:
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		const GLchar* vertex_shader_source[] =
		{
			"#version 430 core							\n"
			"											\n"
			"layout(location = 0) in vec4 offset;		\n"
			"											\n"
			"out vec4 vs_color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),	\n"
			"										vec4(-0.25, 0.25, 0.5, 1.0),\n"
			"										vec4(0.25, 0.25, 0.5, 1.0));\n"
			"	gl_Position = vertices[gl_VertexID] + offset;					\n"
			"																	\n"
			"	const vec4 colors[3] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),		\n"
			"							vec4(0.0, 1.0, 0.0, 1.0),				\n"
			"							vec4(0.0, 0.0, 1.0, 1.0));				\n"
			"	vs_color = colors[gl_VertexID];									\n"
			"}											\n"
		};

		const GLchar* fragment_shader_source[] =
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

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

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
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	virtual void shutdown() {
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}

	virtual void render(double currentTime) {
		const GLfloat red[] = { (float)sin(currentTime) * 0.5f + 0.5f,
								(float)cos(currentTime) * 0.5f + 0.5f,
								(float)sin(currentTime) * 0.5f + 0.5f,
								1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		glUseProgram(rendering_program);

		GLfloat attrib[] = { (float)sin(currentTime) * 0.5f,
							(float)cos(currentTime) * 0.5f,
							0.0f, 0.0f };

		glVertexAttrib4fv(0, attrib);

		glPointSize(40.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}



private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

//DECLARE_MAIN(my_application);

