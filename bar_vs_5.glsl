#version 430 core

layout(location = 3) in float ct;
out vec4 vs_color;

void main(void)
{
	const vec4 vertices[6] = vec4[6](vec4(-0.01, 0.0, 0.5, 1.0),
										vec4(-0.01, -1.0, 0.5, 1.0),
										vec4(0.01, -1.0, 0.5, 1.0),

										vec4(-0.01, 0.0, 0.5, 1.0),
										vec4(0.01, -1.0, 0.5, 1.0),
										vec4(0.01, 0.0, 0.5, 1.0));

	mat4 mx;
	mx[0] = vec4(1.0, 0.0, 0.0, 0.0);
	mx[1] = vec4(0.0, 1.0, 0.0, 0.0);
	mx[2] = vec4(0.0, 0.0, 1.0, 0.0);
	mx[3] = vec4(sin(ct) * 0.5, 0.0, 0.0, 1.0);

	vec3 eyePos = vec3(0.2, 0.3, 0.8);
	vec3 target = vec3(0.0, 0.0, 0.5);
	vec3 upVec = vec3(0.0, 1.0, 0.0);

	float left = -0.1;
	float right = 0.1;
	float top = 0.07;
	float bottom = -0.07;
	float near = 0.1;
	float far = 10;

	vec3 vec_D = (eyePos - target) / length(eyePos - target);
	vec3 vec_R = cross(upVec, vec_D);
	vec3 vec_U = cross(vec_D, vec_R);

	mat4 Look1;
	Look1[0] = vec4(vec_R[0], vec_U[0], vec_D[0], 0.0);
	Look1[1] = vec4(vec_R[1], vec_U[1], vec_D[1], 0.0);
	Look1[2] = vec4(vec_R[2], vec_U[2], vec_D[2], 0.0);
	Look1[3] = vec4(0.0, 0.0, 0.0, 1.0);

	mat4 Look2;
	Look2[0] = vec4(1.0, 0.0, 0.0, 0.0);
	Look2[1] = vec4(0.0, 1.0, 0.0, 0.0);
	Look2[2] = vec4(0.0, 0.0, 1.0, 0.0);
	Look2[3] = vec4(-eyePos[0], -eyePos[1], -eyePos[2], 1.0);

	mat4 LookAt = Look1 * Look2;

	mat4 projection;
	projection[0] = vec4((2 * near) / (right - left), 0.0, 0.0, 0.0);
	projection[1] = vec4(0.0, (2 * near) / (top - bottom), 0.0, 0.0);
	projection[2] = vec4((right + left) / (right - left), (top + bottom) / (top - bottom), (near + far) / (near - far), -1.0);
	projection[3] = vec4(0.0, 0.0, (2 * near * far) / (near - far), 0.0);

	gl_Position = projection * LookAt * mx * vertices[gl_VertexID];

	vs_color = vec4(1.0, 0.0, 1.0, 1.0);
}