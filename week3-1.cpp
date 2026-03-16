#include <sb7.h>
#include <vmath.h>

class my_application : public sb7::application {
public:
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint tcs, tes, gs; //테셀 컨트롤, 테셀 이벨류, 지오메트리
		GLuint fragment_shader;
		GLuint program;

		// Vertex Shader
		const GLchar* vertex_shader_source[] =
		{
			"#version 430 core							\n"
			"											\n"
			"layout(location = 0) in vec4 offset;		\n"
			"layout(location = 1) in vec4 color;		\n"
			"											\n"
			"out vec4 vs_color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25, 0.25, 0.5, 1.0),	\n"
			"										vec4(0.25, -0.25, 0.5, 1.0),\n"
			"										vec4(-0.25, 0.25, 0.5, 1.0));\n"
			"	gl_Position = vertices[gl_VertexID] + offset;					\n"
			"	vs_color = color;												\n"
			"}											\n"
		};

		// TCS
		const GLchar* tcs_source[] = {
			"#version 430 core																\n"
			"																				\n"
			"layout (vertices = 3) out;														\n"
			"																				\n"
			"void main(void)																\n"
			"{																				\n"
			"	if (gl_InvocationID == 0) {													\n"
			"		gl_TessLevelInner[0] = 5.0;												\n"
			"		gl_TessLevelOuter[0] = 5.0;												\n"
			"		gl_TessLevelOuter[1] = 5.0;												\n"
			"		gl_TessLevelOuter[2] = 5.0;												\n"
			"	}																			\n"
			"	gl_out[gl_InvocationID].gl_Position= gl_in[gl_InvocationID].gl_Position;	\n"
			"}																				\n"
		};

		// TES
		const GLchar* tes_source[] = {
			"#version 430 core																\n"
			"																				\n"
			"layout(triangles, equal_spacing, cw) in;										\n"
			"																				\n"
			"void main(void)																\n"
			"{																				\n"
			"	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +						\n"
			"					gl_TessCoord.y * gl_in[1].gl_Position +						\n"
			"					gl_TessCoord.z * gl_in[2].gl_Position);						\n"
			"}																				\n"
		};

		// GS
		const GLchar* gs_source[] = {
			"#version 430 core																\n"
			"																				\n"
			"layout(triangles) in;															\n"
			"layout(points, max_vertices = 6) out;											\n"
			"																				\n"
			"void main(void)																\n"
			"{																				\n"
			"	int i;																		\n"
			"	for (i = 0; i < gl_in.length(); i++) {										\n"
			"		gl_Position = gl_in[i].gl_Position;										\n"
			"		EmitVertex();															\n"
			"		gl_Position[0] *= -1;													\n"
			"		gl_Position[1] *= -1;													\n"
			"		EmitVertex();															\n"
			"	}																			\n"
			"}																				\n"
		};

		// Fragment Shader
		const GLchar* fragment_shader_source[] =
		{
			"#version 430 core							\n"
			"											\n"
			"out vec4 color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);		\n"
			"}											\n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tcs, 1, tcs_source, NULL);
		glCompileShader(tcs);
		
		tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tes, 1, tes_source, NULL);
		glCompileShader(tes);

		gs = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gs, 1, gs_source, NULL);
		glCompileShader(gs);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, tcs);
		glAttachShader(program, tes);
		glAttachShader(program, gs);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		glDeleteShader(tcs);
		glDeleteShader(tes);
		glDeleteShader(gs);

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

		GLfloat color[] = { 1.0f, 0.0f, 0.0f, 0.0f };

		glVertexAttrib4fv(1, color);

		glPointSize(5.0f);
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawArrays(GL_PATCHES, 0, 3);
	}



private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

//DECLARE_MAIN(my_application);
