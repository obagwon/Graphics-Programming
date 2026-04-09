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

		vertex_shader = sb7::shader::load("week6-hw_vs.glsl", GL_VERTEX_SHADER);

		fragment_shader = sb7::shader::load("week6-hw_fs.glsl", GL_FRAGMENT_SHADER);

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

		GLfloat vertices[] = {
			// 앞 123 324
			-0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 
			-0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 
			0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f,

			0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f,
			0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f,

			// 뒤 132 342
			-0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
			0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f,

			0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
			0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f,

			// 위
			-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
			-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
			0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f,

			0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
			-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
			0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f,

			// 아래
			-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
			0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
			-0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 0.0f,

			0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
			0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
			-0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 0.0f,

			// 좌
			-0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
			-0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 1.0f,
			-0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
			
			-0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
			-0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 1.0f,
			-0.25f, -0.25f, -0.25f, 0.0f, 0.0f, 1.0f,
			
			// 우
			0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 1.0f,
			
			0.25f, 0.25f, -0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, -0.25f, 0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, -0.25f, -0.25f, 0.0f, 0.0f, 1.0f
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	virtual void shutdown() {
		glDeleteVertexArrays(1, &vertex_array_object);
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

		vmath::mat4 rm = vmath::rotate(angle, 0.0f, 1.0f, 0.0f);
		GLuint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);

		vmath::mat4 tm = vmath::translate((float)sin(currentTime) * 2, 0.0f, (float)cos(currentTime) * 2);
		GLuint transMatLocation = glGetUniformLocation(rendering_program, "transMat");
		glUniformMatrix4fv(transMatLocation, 1, GL_FALSE, tm);

		vmath::vec3 eye(5.0, 2.0, 3.0);
		vmath::vec3 center(0.0, 0.0, 0.0);
		vmath::vec3 up(0.0, 1.0, 0.0);
		vmath::mat4 vm = vmath::lookat(eye, center, up);
		GLuint viewMatLocation = glGetUniformLocation(rendering_program, "viewMat");
		glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, vm);
		
		vmath::mat4 pm = vmath::perspective(50.0f, info.windowWidth / info.windowHeight, 0.1f, 1000.0f);
		GLuint perMatLocation = glGetUniformLocation(rendering_program, "perMat");
		glUniformMatrix4fv(perMatLocation, 1, GL_FALSE, pm);
		
		

		glBindVertexArray(vertex_array_object);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(my_application);

