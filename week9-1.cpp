#include <sb7.h>
#include <vmath.h>
#include <shader.h>

// ϴ ͸ ּ
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

struct Mesh
{
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	GLsizei indexCount = 0;
};

class my_application : public sb7::application {
public:
	//  ̴
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		vertex_shader = sb7::shader::load("week9-1_vs.glsl", GL_VERTEX_SHADER);

		fragment_shader = sb7::shader::load("week9-1_fs.glsl", GL_FRAGMENT_SHADER);

		program = glCreateProgram();
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
			// position                // color               // texcoord    // normal

			// front (+z)
			 0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
			-0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,    0.0f, 0.0f, 1.0f,
			-0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
			 0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 0.0f, 1.0f,

			 // back (-z)
			  0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
			 -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,    0.0f, 0.0f, -1.0f,
			 -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
			  0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 0.0f, -1.0f,

			  // left (-x)
			  -0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
			  -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
			  -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
			  -0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

			  // right (+x)
			  0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    1.0f, 0.0f, 0.0f,
			  0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,    1.0f, 0.0f, 0.0f,
			  0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
			  0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    1.0f, 0.0f, 0.0f,

			  // top (+y)
			   0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
			  -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
			  -0.25f,  0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
			   0.25f,  0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 1.0f, 0.0f,

			   // bottom (-y)
				0.25f, -0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    0.0f, -1.0f, 0.0f,
			   -0.25f, -0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,    0.0f, -1.0f, 0.0f,
			   -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
				0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, -1.0f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,       // 

			4, 6, 5,
			4, 7, 6,       // 

			8, 9, 10,
			8, 10, 11,     // 

			12, 13, 14,
			12, 14, 15,    // 

			16, 17, 18,
			16, 18, 19,    // 

			20, 21, 22,
			20, 22, 23     // Ʒ
		};

		glGenVertexArrays(1, &mesh.vao);
		glBindVertexArray(mesh.vao);

		glGenBuffers(1, &mesh.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &mesh.ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);

		mesh.indexCount = 36;
		return mesh;
	}

	Mesh createRoom()
	{
		Mesh mesh;

		GLfloat vertices[] = {
			// position                // color               // texcoord

			// պ (+z) : ο    
			 0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    0.0f, 3.0f,
			-0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    3.0f, 3.0f,
			-0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    3.0f, 0.0f,
			 0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,

			 // ں (-z)
			  0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    3.0f, 3.0f,
			 -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 3.0f,
			 -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
			  0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    3.0f, 0.0f,

			  // ޺ (-x)
			  -0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    0.0f, 3.0f,
			  -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    3.0f, 3.0f,
			  -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    3.0f, 0.0f,
			  -0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,

			  //  (+x)
			   0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    0.0f, 3.0f,
			   0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    3.0f, 3.0f,
			   0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    3.0f, 0.0f,
			   0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,

			   // ٴ (-y)
				0.25f, -0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    3.0f, 3.0f,
			   -0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 0.0f,    0.0f, 3.0f,
			   -0.25f, -0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
				0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    3.0f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,       // 

			4, 6, 5,
			4, 7, 6,       // 

			8, 9, 10,
			8, 10, 11,     // 

			12, 13, 14,
			12, 14, 15,    // 

			16, 17, 18,
			16, 18, 19     // Ʒ
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

		mesh.indexCount = 30;
		return mesh;
	}

	Mesh createCri()
	{
		Mesh mesh;

		GLfloat vertices[] = {
			// position                 // color                // texcoord

			// 
			0.0f,   0.5f,  0.0f,        1.0f, 1.0f, 1.0f,      0.5f, 1.0f,
		   -0.25f,  0.0f, 0.25f,       1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
			0.25f,  0.0f, 0.25f,       1.0f, 1.0f, 0.0f,      1.0f, 0.0f,

			// 
			0.0f,   0.5f,  0.0f,        1.0f, 1.0f, 1.0f,      0.5f, 1.0f,
			0.25f,  0.0f, -0.25f,      0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
		   -0.25f,  0.0f, -0.25f,      0.0f, 1.0f, 1.0f,      1.0f, 0.0f,

		   // 
		   0.0f,   0.5f,  0.0f,        1.0f, 1.0f, 1.0f,      0.5f, 1.0f,
		  -0.25f,  0.0f, -0.25f,      0.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		  -0.25f,  0.0f,  0.25f,      1.0f, 0.0f, 0.0f,      1.0f, 0.0f,

		  // 
		  0.0f,   0.5f,  0.0f,        1.0f, 1.0f, 1.0f,      0.5f, 1.0f,
		  0.25f,  0.0f,  0.25f,      1.0f, 1.0f, 0.0f,      0.0f, 0.0f,
		  0.25f,  0.0f, -0.25f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f,

		  // ؾ
			0.0f,   -0.5f,  0.0f,        0.0f, 0.0f, 0.0f,      0.5f, 1.0f,
		   0.25f,  0.0f, 0.25f,       1.0f, 1.0f, 0.0f,      0.0f, 0.0f,
			-0.25f,  0.0f, 0.25f,       1.0f, 0.0f, 0.0f,      1.0f, 0.0f,

			// ص
			0.0f,   -0.5f,  0.0f,        0.0f, 0.0f, 0.0f,      0.5f, 1.0f,
			-0.25f,  0.0f, -0.25f,      0.0f, 1.0f, 1.0f,      0.0f, 0.0f,
			0.25f,  0.0f, -0.25f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f,

			// 
			0.0f,   -0.5f,  0.0f,        0.0f, 0.0f, 0.0f,      0.5f, 1.0f,
		   -0.25f,  0.0f, 0.25f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
		   -0.25f,  0.0f,  -0.25f,      0.0f, 1.0f, 1.0f,      1.0f, 0.0f,

		   // ؿ
		   0.0f,   -0.5f,  0.0f,        0.0f, 0.0f, 0.0f,      0.5f, 1.0f,
		   0.25f,  0.0f,  -0.25f,      0.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		   0.25f,  0.0f, 0.25f,      1.0f, 1.0f, 0.0f,      1.0f, 0.0f,

		};

		GLuint indices[] = {
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,

			12,13,14,
			15,16,17,
			18,19,20,
			21,22,23
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

		mesh.indexCount = 24;
		return mesh;
	}

	Mesh createPlane()
	{
		Mesh mesh;

		GLfloat vertices[] = {
			// position                 // color              // texcoord

			 0.5f, 0.0f, -0.5f,        1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
			-0.5f, 0.0f, -0.5f,        1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
			-0.5f, 0.0f,  0.5f,        1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
			 0.5f, 0.0f,  0.5f,        1.0f, 1.0f, 1.0f,    1.0f, 0.0f
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

	GLuint loadTexture(const char* filename)
	{
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (data)
		{
			GLint format = GL_RGB;
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

	GLuint loadTextureB(const char* filename)
	{
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (data)
		{
			GLint format = GL_RGB;
			if (nrChannels == 1) format = GL_RED;
			else if (nrChannels == 3) format = GL_RGB;
			else if (nrChannels == 4) format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		float borderColor[] = { 0.9f, 0.7f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		return tex;
	}

	void drawCube(const Mesh& mesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		const GLuint textures[6],
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime,
		int renderMode = 4)
	{
		vmath::mat4 model =
			vmath::translate(position) *
			vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
			vmath::scale(scaleValue);

		glUseProgram(rendering_program);

		glUniformMatrix4fv(loc_model, 1, GL_FALSE, model);
		glUniformMatrix4fv(loc_view, 1, GL_FALSE, view);
		glUniformMatrix4fv(loc_proj, 1, GL_FALSE, proj);
		glUniform1f(loc_time, (float)currentTime);
		glUniform1i(loc_renderMode, renderMode);
		glUniform1f(loc_alpha, (float)sin(currentTime) * 0.5f + 0.5f);

		glBindVertexArray(mesh.vao);

		for (int face = 0; face < 6; face++)
		{
			if (renderMode != 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures[face]);
				glUniform1i(loc_tex, 0);
			}

			glDrawElements(
				GL_TRIANGLES,
				6,
				GL_UNSIGNED_INT,
				(void*)(face * 6 * sizeof(GLuint))
			);
		}

		glBindVertexArray(0);
	}

	void drawRoom(const Mesh& mesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		const GLuint textures[5],
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime,
		int renderMode = 0)
	{
		vmath::mat4 model =
			vmath::translate(position) *
			vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
			vmath::scale(scaleValue);

		glUseProgram(rendering_program);

		glUniformMatrix4fv(loc_model, 1, GL_FALSE, model);
		glUniformMatrix4fv(loc_view, 1, GL_FALSE, view);
		glUniformMatrix4fv(loc_proj, 1, GL_FALSE, proj);
		glUniform1f(loc_time, (float)currentTime);

		glBindVertexArray(mesh.vao);

		for (int face = 0; face < 5; face++)
		{
			int faceRenderMode = renderMode;

			// Ʒ(face == 4) ؽó +  ȥ
			if (face == 4)
				faceRenderMode = 2;
			else faceRenderMode = 3;

			glUniform1i(loc_renderMode, faceRenderMode);

			if (faceRenderMode != 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures[face]);
				glUniform1i(loc_tex, 0);
			}

			glDrawElements(
				GL_TRIANGLES,
				6,
				GL_UNSIGNED_INT,
				(void*)(face * 6 * sizeof(GLuint))
			);
		}

		glBindVertexArray(0);
	}

	void drawCri(const Mesh& mesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		const GLuint textures[4],
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime,
		int renderMode = 1)
	{
		vmath::mat4 model =
			vmath::translate(position) *
			vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
			vmath::scale(scaleValue);

		glUseProgram(rendering_program);

		glUniformMatrix4fv(loc_model, 1, GL_FALSE, model);
		glUniformMatrix4fv(loc_view, 1, GL_FALSE, view);
		glUniformMatrix4fv(loc_proj, 1, GL_FALSE, proj);
		glUniform1f(loc_time, (float)currentTime);
		glUniform1i(loc_renderMode, renderMode);

		glBindVertexArray(mesh.vao);

		for (int face = 0; face < 8; face++)
		{
			if (renderMode != 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures[face]);
				glUniform1i(loc_tex, 0);
			}

			glDrawElements(
				GL_TRIANGLES,
				3,
				GL_UNSIGNED_INT,
				(void*)(face * 3 * sizeof(GLuint))
			);
		}

		glBindVertexArray(0);
	}

	void drawPlane(const Mesh& mesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		GLuint texture,
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime,
		int renderMode = 0)
	{
		vmath::mat4 model =
			vmath::translate(position) *
			vmath::rotate(rotation[0], rotation[1], rotation[2], rotation[3]) *
			vmath::scale(scaleValue);

		glUseProgram(rendering_program);

		glUniformMatrix4fv(loc_model, 1, GL_FALSE, model);
		glUniformMatrix4fv(loc_view, 1, GL_FALSE, view);
		glUniformMatrix4fv(loc_proj, 1, GL_FALSE, proj);
		glUniform1f(loc_time, (float)currentTime);
		glUniform1i(loc_renderMode, renderMode);
		glUniform1f(loc_alpha, (float)sin(currentTime) * 0.5f + 0.5f);

		if (renderMode != 1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(loc_tex, 0);
		}

		glBindVertexArray(mesh.vao);

		glDrawElements(
			GL_TRIANGLES,
			mesh.indexCount,
			GL_UNSIGNED_INT,
			(void*)0
		);

		glBindVertexArray(0);
	}

	virtual void startup() {
		stbi_set_flip_vertically_on_load(true);

		rendering_program = compile_shaders();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		roomMesh = createRoom();
		cubeMesh = createCube();
		criMesh = createCri();
		planeMesh = createPlane();

		texFloor = loadTexture("mario_brick_floor.jpg");
		texCubeSide = loadTextureB("mario_box_side.png");
		texCubeUD = loadTextureB("mario_box_base.png");
		texBg = loadTexture("mario_star_background.jpg");
		texPlane = loadTexture("wall.jpg");

		loc_model = glGetUniformLocation(rendering_program, "u_model");
		loc_view = glGetUniformLocation(rendering_program, "u_view");
		loc_proj = glGetUniformLocation(rendering_program, "u_proj");
		loc_tex = glGetUniformLocation(rendering_program, "u_tex");
		loc_time = glGetUniformLocation(rendering_program, "u_time");
		loc_renderMode = glGetUniformLocation(rendering_program, "u_renderMode");
		loc_alpha = glGetUniformLocation(rendering_program, "alphaK");

		loc_lightPos = glGetUniformLocation(rendering_program, "lightPos");
		loc_lightColor = glGetUniformLocation(rendering_program, "lightColor");
		loc_objectColor = glGetUniformLocation(rendering_program, "objectColor");
		loc_viewPos = glGetUniformLocation(rendering_program, "viewPos");
	}

	virtual void shutdown() {
		// ̴ α׷ 
		glDeleteProgram(rendering_program);

		// roomMesh 
		glDeleteVertexArrays(1, &roomMesh.vao);
		glDeleteBuffers(1, &roomMesh.vbo);
		glDeleteBuffers(1, &roomMesh.ebo);

		// cubeMesh 
		glDeleteVertexArrays(1, &cubeMesh.vao);
		glDeleteBuffers(1, &cubeMesh.vbo);
		glDeleteBuffers(1, &cubeMesh.ebo);

		// criMesh 
		glDeleteVertexArrays(1, &criMesh.vao);
		glDeleteBuffers(1, &criMesh.vbo);
		glDeleteBuffers(1, &criMesh.ebo);

		// ؽó 
		glDeleteTextures(1, &texFloor);
		glDeleteTextures(1, &texCubeSide);
		glDeleteTextures(1, &texCubeUD);
		glDeleteTextures(1, &texBg);
		glDeleteTextures(1, &texPlane);
	}

	virtual void render(double currentTime) {
		const GLfloat black[] = { 0.0,
								0.0,
								0.0,
								1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		vmath::vec3 eye((float)cos(currentTime * 0.5f) * 3.0f, 2.0f, (float)sin(currentTime * 0.5f) * 3.0f);
		//vmath::vec3 eye(5.0f, 2.0f, 3.0f);
		vmath::vec3 center(0.0f, 0.0f, 0.0f);
		vmath::vec3 up(0.0f, 1.0f, 0.0f);

		vmath::mat4 view = vmath::lookat(eye, center, up);
		vmath::mat4 proj = vmath::perspective(
			50.0f,
			(float)info.windowWidth / (float)info.windowHeight,
			0.1f,
			1000.0f
		);

		glUseProgram(rendering_program);

		vmath::vec3 lightPos(1.5f, 2.0f, 2.0f);
		vmath::vec3 lightColor(1.0f, 1.0f, 1.0f);
		vmath::vec3 boxColor(1.0f, 0.5f, 0.31f);
		glUniform3fv(loc_lightPos, 1, lightPos);
		glUniform3fv(loc_lightColor, 1, lightColor);
		glUniform3fv(loc_objectColor, 1, boxColor);
		glUniform3fv(loc_viewPos, 1, eye);

		GLuint cubeTex[6] = {
			texCubeSide,
			texCubeSide,
			texCubeSide,
			texCubeSide,
			texCubeUD,
			texCubeUD,
		};

		drawCube(cubeMesh,
			vmath::vec3(0.0f, 0.0f, 0.0f),
			vmath::vec3(1.0f, 1.0f, 1.0f),
			vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			cubeTex,
			view, proj, currentTime, 5);

		drawPlane(planeMesh,
			vmath::vec3(0.0f, -0.25f -0.01f, 0.0f),
			vmath::vec3(5.0f, 1.0f, 5.0f),
			vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			texPlane,
			view, proj, currentTime, 0);
	}

private:
	GLuint rendering_program;

	Mesh roomMesh;
	Mesh cubeMesh;
	Mesh criMesh;
	Mesh planeMesh;

	GLuint texFloor = 0;
	GLuint texCubeSide = 0;
	GLuint texCubeUD = 0;
	GLuint texBg = 0;
	GLuint texPlane = 0;

	GLint loc_model = -1;
	GLint loc_view = -1;
	GLint loc_proj = -1;
	GLint loc_tex = -1;
	GLint loc_time = -1;
	GLint loc_renderMode = -1;
	GLint loc_alpha = -1;

	GLint loc_lightPos = -1;
	GLint loc_lightColor = -1;
	GLint loc_objectColor = -1;
	GLint loc_viewPos = -1;
};

DECLARE_MAIN(my_application);

