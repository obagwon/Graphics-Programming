#include <sb7.h>
#include <vmath.h>

class my_application : public sb7::application {
public:
	// 컴파일 쉐이더
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		const GLchar* vertex_shader_source[] =
		{
			"#version 430 core							\n"
			"											\n"
			"layout(location = 0) in vec4 color;		\n"
			"layout(location = 1) in vec4 color2;		\n"
			"layout(location = 2) in vec4 color3;		\n"
			"layout(location = 3) in float ct;			\n"
			"											\n"
			"out vec4 vs_color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	const vec4 vertices[12] = vec4[12](vec4(0.0, 0.0, 0.5, 1.0),	\n"
			"										vec4(0.25, 0.0, 0.5, 1.0),\n"
			"										vec4(0.25, 0.25, 0.5, 1.0),\n"

			"										vec4(0.0, 0.0, 0.5, 1.0),\n"
			"										vec4(0.0, 0.25, 0.5, 1.0),\n"
			"										vec4(-0.25, 0.25, 0.5, 1.0),\n"

			"										vec4(0.0, 0.0, 0.5, 1.0),\n"
			"										vec4(-0.25, 0.0, 0.5, 1.0),\n"
			"										vec4(-0.25, -0.25, 0.5, 1.0),\n"

			"										vec4(0.0, 0.0, 0.5, 1.0),\n"
			"										vec4(0.0, -0.25, 0.5, 1.0),\n"
			"										vec4(0.25, -0.25, 0.5, 1.0));\n"
			
			"	mat4 mrz;\n"
			"	mrz[0] = vec4(cos(ct), sin(ct), 0.0, 0.0);\n"
			"	mrz[1] = vec4(-sin(ct), cos(ct), 0.0, 0.0);\n"
			"	mrz[2] = vec4(0.0, 0.0, 1.0, 0.0);\n"
			"	mrz[3] = vec4(0.0, 0.0, 0.0, 1.0);\n"
			"												\n"
			"	mat4 mx;\n"
			"	mx[0] = vec4(1.0, 0.0, 0.0, 0.0);\n"
			"	mx[1] = vec4(0.0, 1.0, 0.0, 0.0);\n"
			"	mx[2] = vec4(0.0, 0.0, 1.0, 0.0);\n"
			"	mx[3] = vec4(sin(ct), 0.0, 0.0, 1.0);\n"

			"	gl_Position = mx * mrz * vertices[gl_VertexID];					\n"
			"																	\n"
			"	const vec4 colors[3] = vec4[3](color, color2, color3);				\n"
			"	vs_color = colors[gl_VertexID % 3];									\n"
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

	// 컴파일 쉐이더 2
	GLuint compile_shaders2(void) {
		GLuint vertex_shader2;
		GLuint fragment_shader2;
		GLuint program2;

		const GLchar* vertex_shader_source2[] =
		{
			"#version 430 core							\n"
			"											\n"
			"layout(location = 3) in float ct;			\n"
			"out vec4 vs_color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	const vec4 vertices[6] = vec4[6](vec4(-0.01, 0.0, 0.5, 1.0),	\n"
			"										vec4(-0.01, -1.0, 0.5, 1.0),\n"
			"										vec4(0.01, -1.0, 0.5, 1.0),\n"

			"										vec4(-0.01, 0.0, 0.5, 1.0),\n"
			"										vec4(0.01, -1.0, 0.5, 1.0),\n"
			"										vec4(0.01, 0.0, 0.5, 1.0));\n"

			"	mat4 mx;\n"
			"	mx[0] = vec4(1.0, 0.0, 0.0, 0.0);\n"
			"	mx[1] = vec4(0.0, 1.0, 0.0, 0.0);\n"
			"	mx[2] = vec4(0.0, 0.0, 1.0, 0.0);\n"
			"	mx[3] = vec4(sin(ct), 0.0, 0.0, 1.0);\n"

			"	gl_Position = mx * vertices[gl_VertexID];							\n"
			"																	\n"
			"	vs_color = vec4(1.0, 0.0, 1.0, 1.0);								\n"
			"}											\n"
		};

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

		vertex_shader2 = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader2, 1, vertex_shader_source2, NULL);
		glCompileShader(vertex_shader2);

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

		GLfloat attrib[] = { (float)sin(currentTime) * 0.5f + 0.5f,
							(float)cos(currentTime) * 0.5f + 0.5f,
							(float)sin(currentTime) * 0.5f + 0.5f,
							0.0f };
		GLfloat attrib2[] = { (float)cos(currentTime) * 0.5f + 0.5f,
							(float)sin(currentTime) * 0.5f + 0.5f,
							(float)sin(currentTime) * 0.5f + 0.5f,
							0.0f };
		GLfloat attrib3[] = { (float)cos(currentTime) * 0.5f + 0.5f,
							(float)sin(currentTime) * 0.5f + 0.5f,
							(float)sin(currentTime) * 0.5f + 0.5f,
							0.0f };

		glVertexAttrib4fv(0, attrib);
		glVertexAttrib4fv(1, attrib2);
		glVertexAttrib4fv(2, attrib3);
		glVertexAttrib1f(3, (float)currentTime);

		glUseProgram(rendering_program2);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glUseProgram(rendering_program);
		glDrawArrays(GL_TRIANGLES, 0, 12);

	}



private:
	GLuint rendering_program;
	GLuint rendering_program2;
	GLuint vertex_array_object;
};

DECLARE_MAIN(my_application);

