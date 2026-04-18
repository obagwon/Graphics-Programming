#include <sb7.h>
#include <vmath.h>
#include <shader.h>

// 실행하는 것만 주석해제
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
	// 컴파일 쉐이더
	GLuint compile_shaders(void) {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		vertex_shader = sb7::shader::load("weekmidmid_vs.glsl", GL_VERTEX_SHADER);

		fragment_shader = sb7::shader::load("weekmidmid_fs.glsl", GL_FRAGMENT_SHADER);

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
			// position                // color               // texcoord

			// 앞
			 0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.1f, 1.1f,
			-0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    -0.1f, 1.1f,
			-0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    -0.1f, -0.1f,
			 0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.1f, -0.1f,

			 // 뒤
			  0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.1f, 1.1f,
			 -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    -0.1f, 1.1f,
			 -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    -0.1f, -0.1f,
			  0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.1f, -0.1f,

			  // 좌
			  -0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.1f, 1.1f,
			  -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    -0.1f, 1.1f,
			  -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    -0.1f, -0.1f,
			  -0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.1f, -0.1f,

			  // 우
			  0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.1f, 1.1f,
			  0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    -0.1f, 1.1f,
			  0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    -0.1f, -0.1f,
			  0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.1f, -0.1f,

			  // 위
			   0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
			  -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
			  -0.25f,  0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
			   0.25f,  0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

			   // 아래
				0.25f, -0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
			   -0.25f, -0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
			   -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
				0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,       // 앞

			4, 6, 5,
			4, 7, 6,       // 뒤

			8, 9, 10,
			8, 10, 11,     // 좌

			12, 13, 14,
			12, 14, 15,    // 우

			16, 17, 18,
			16, 18, 19,    // 위

			20, 21, 22,
			20, 22, 23     // 아래
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

	Mesh createRoom()
	{
		Mesh mesh;

		GLfloat vertices[] = {
			// position                // color               // texcoord

			// 앞벽 (+z) : 내부에서 볼 때 정상 방향
			 0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
			-0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
			-0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
			 0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,

			 // 뒤벽 (-z)
			  0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
			 -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
			 -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
			  0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

			  // 왼벽 (-x)
			  -0.25f,  0.25f,  0.25f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
			  -0.25f,  0.25f, -0.25f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
			  -0.25f, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
			  -0.25f, -0.25f,  0.25f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,

			  // 오른벽 (+x)
			   0.25f,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
			   0.25f,  0.25f,  0.25f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
			   0.25f, -0.25f,  0.25f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
			   0.25f, -0.25f, -0.25f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,

			   // 바닥 (-y)
				0.25f, -0.25f,  0.25f,    0.6f, 0.9f, 1.5f,    1.0f, 1.0f,
			   -0.25f, -0.25f,  0.25f,    0.6f, 0.9f, 1.5f,    0.0f, 1.0f,
			   -0.25f, -0.25f, -0.25f,    0.6f, 0.9f, 1.5f,    0.0f, 0.0f,
				0.25f, -0.25f, -0.25f,    0.6f, 0.9f, 1.5f,    1.0f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,       // 앞

			4, 6, 5,
			4, 7, 6,       // 뒤

			8, 9, 10,
			8, 10, 11,     // 좌

			12, 13, 14,
			12, 14, 15,    // 우

			16, 17, 18,
			16, 18, 19     // 아래
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

	Mesh createRoof()
	{
		Mesh mesh;

		GLfloat vertices[] = {
			// position                 // color                // texcoord

			// 앞
			0.0f,   0.5f,  0.0f,        1.0f, 0.0f, 0.0f,      0.5f, 1.0f,
		   -0.25f,  0.25f, 0.25f,       1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
			0.25f,  0.25f, 0.25f,       1.0f, 0.0f, 0.0f,      1.0f, 0.0f,

			// 뒤
			0.0f,   0.5f,  0.0f,        1.0f, 1.0f, 0.0f,      0.5f, 1.0f,
			0.25f,  0.25f, -0.25f,      1.0f, 1.0f, 0.0f,      0.0f, 0.0f,
		   -0.25f,  0.25f, -0.25f,      1.0f, 1.0f, 0.0f,      1.0f, 0.0f,

		   // 좌
		   0.0f,   0.5f,  0.0f,        0.0f, 1.0f, 0.0f,      0.5f, 1.0f,
		  -0.25f,  0.25f, -0.25f,      0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
		  -0.25f,  0.25f,  0.25f,      1.0f, 0.0f, 0.0f,      1.0f, 0.0f,

		  // 우
		  0.0f,   0.5f,  0.0f,        0.0f, 0.0f, 1.0f,      0.5f, 1.0f,
		  0.25f,  0.25f,  0.25f,      0.0f, 0.0f, 1.0f,      0.0f, 0.0f,
		  0.25f,  0.25f, -0.25f,      0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
		};

		GLuint indices[] = {
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11
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

		mesh.indexCount = 12;
		return mesh;
	}

	Mesh createWater()
	{
		Mesh mesh;

		GLfloat vertices[] = {
			// position                  // color               // texcoord
			 0.5f, 0.0f, -0.5f,          1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
			-0.5f, 0.0f, -0.5f,          1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
			-0.5f, 0.0f,  0.5f,          1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
			 0.5f, 0.0f,  0.5f,          1.0f, 1.0f, 1.0f,      1.0f, 0.0f
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

		float borderColor[] = { 0.5f, 0.4f, 0.3f, 1.0f };
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

			// 아랫면(face == 4)만 텍스처 + 색상 혼합
			if (face == 4)
				faceRenderMode = 2;

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

	void drawRoof(const Mesh& mesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		const GLuint textures[4],
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

		glBindVertexArray(mesh.vao);

		for (int face = 0; face < 4; face++)
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

	void drawHouse(const Mesh& cubeMesh,
		const Mesh& roofMesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		const GLuint cubeTextures[6],
		const GLuint roofTextures[4],
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime,
		int renderMode = 0)
	{
		drawCube(
			cubeMesh,
			position,
			scaleValue,
			rotation,
			cubeTextures,
			view,
			proj,
			currentTime,
			renderMode
		);

		drawRoof(
			roofMesh,
			position,
			scaleValue,
			rotation,
			roofTextures,
			view,
			proj,
			currentTime,
			renderMode
		);
	}

	void drawWater(const Mesh& mesh,
		const vmath::vec3& position,
		const vmath::vec3& scaleValue,
		const vmath::vec4& rotation,
		GLuint texture,
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime)
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

		// water 전용 모드
		glUniform1i(loc_renderMode, 3);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(loc_tex, 0);

		glBindVertexArray(mesh.vao);
		glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void drawRiver(const Mesh& waterMesh,
		GLuint texWater,
		const vmath::mat4& view,
		const vmath::mat4& proj,
		double currentTime)
	{
		drawWater(waterMesh,
			vmath::vec3(-2.8f, -4.68f, 2.6f),
			vmath::vec3(1.6f, 1.0f, 1.0f),
			vmath::vec4(42.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(-2.0f, -4.68f, 1.9f),
			vmath::vec3(1.7f, 1.0f, 1.0f),
			vmath::vec4(35.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(-1.2f, -4.68f, 1.2f),
			vmath::vec3(1.8f, 1.0f, 1.0f),
			vmath::vec4(27.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(-0.3f, -4.68f, 0.5f),
			vmath::vec3(1.9f, 1.0f, 1.0f),
			vmath::vec4(18.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(0.7f, -4.68f, -0.2f),
			vmath::vec3(1.9f, 1.0f, 1.0f),
			vmath::vec4(8.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(1.6f, -4.68f, -1.0f),
			vmath::vec3(1.8f, 1.0f, 1.0f),
			vmath::vec4(-4.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(2.5f, -4.68f, -1.8f),
			vmath::vec3(1.7f, 1.0f, 1.0f),
			vmath::vec4(-15.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);

		drawWater(waterMesh,
			vmath::vec3(3.3f, -4.68f, -2.5f),
			vmath::vec3(1.5f, 1.0f, 1.0f),
			vmath::vec4(-26.0f, 0.0f, 1.0f, 0.0f),
			texWater, view, proj, currentTime);
	}

	virtual void startup() {
		stbi_set_flip_vertically_on_load(true);

		rendering_program = compile_shaders();

		roomMesh = createRoom();
		cubeMesh = createCube();
		roofMesh = createRoof();
		waterMesh = createWater();

		texSand = loadTexture("sand.jpg");
		texWater = loadTexture("water.jpg");
		texCubeF = loadTextureB("sand_front.jpg");
		texCubeW = loadTextureB("sand_wall.jpg");
		texRoof = loadTexture("sand_roof.jpg");
		texSky = loadTexture("sky.jpg");

		loc_model = glGetUniformLocation(rendering_program, "u_model");
		loc_view = glGetUniformLocation(rendering_program, "u_view");
		loc_proj = glGetUniformLocation(rendering_program, "u_proj");
		loc_tex = glGetUniformLocation(rendering_program, "u_tex");
		loc_time = glGetUniformLocation(rendering_program, "u_time");
		loc_renderMode = glGetUniformLocation(rendering_program, "u_renderMode");
	}

	virtual void shutdown() {
		glDeleteProgram(rendering_program);
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

		vmath::vec3 eye((float)cos(currentTime) * 1.0f, -2.0f, (float)sin(currentTime) * 1.0f);
		//vmath::vec3 eye(5.0f, -2.0f, 3.0f);
		vmath::vec3 center(0.0f, -3.0f, 0.0f);
		vmath::vec3 up(0.0f, 1.0f, 0.0f);

		vmath::mat4 view = vmath::lookat(eye, center, up);
		vmath::mat4 proj = vmath::perspective(
			50.0f,
			(float)info.windowWidth / (float)info.windowHeight,
			0.1f,
			1000.0f
		);

		GLuint roomTex[5] = {
			texSky,
			texSky,
			texSky,
			texSky,
			texSand
		};

		glFrontFace(GL_CW);
		drawRoom(roomMesh,
			vmath::vec3(0.0f, 0.0f, 0.0f),
			vmath::vec3(20.0f, 20.0f, 20.0f),
			vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			roomTex,
			view, proj, currentTime, 0);
		glFrontFace(GL_CCW);

		GLuint cubeTex[6] = {
			texCubeF,
			texCubeW,
			texCubeW,
			texCubeW,
			0,
			0,
		};
		GLuint roofTex[4] = {
			texRoof,
			texRoof,
			texRoof,
			texRoof
		};

		drawHouse(cubeMesh, roofMesh,
			vmath::vec3(-3.5f, -4.75f, 1.5f),
			vmath::vec3(1.0f, 1.0f, 1.0f),
			vmath::vec4(90, 0.0f, 1.0f, 0.0f),
			cubeTex, roofTex,
			view, proj, currentTime, 0);

		drawHouse(cubeMesh, roofMesh,
			vmath::vec3(0.0f, -4.5f, 2.5f),
			vmath::vec3(2.0f, 2.0f, 2.0f),
			vmath::vec4(120, 0.0f, 1.0f, 0.0f),
			cubeTex, roofTex,
			view, proj, currentTime, 0);

		drawHouse(cubeMesh, roofMesh,
			vmath::vec3(1.0f, -4.5f,-3.0f),
			vmath::vec3(2.0f, 2.0f, 2.0f),
			vmath::vec4(90, 0.0f, 1.0f, 0.0f),
			cubeTex, roofTex,
			view, proj, currentTime, 0);

		drawRiver(waterMesh, texWater, view, proj, currentTime);
	}

private:
	GLuint rendering_program;
	
	Mesh roomMesh;
	Mesh cubeMesh;
	Mesh roofMesh;
	Mesh waterMesh;

	GLuint texSand = 0;
	GLuint texWater = 0;
	GLuint texCubeF = 0;
	GLuint texCubeW = 0;
	GLuint texRoof = 0;
	GLuint texSky = 0;

	GLint loc_model = -1;
	GLint loc_view = -1;
	GLint loc_proj = -1;
	GLint loc_tex = -1;
	GLint loc_time = -1;
	GLint loc_renderMode = -1;
};

DECLARE_MAIN(my_application);

