#pragma once

#include "Include.h"

#include "Shader_Program.h"

struct Camera {
	vec3 position;
	vec3 z_vec = vec3(0.0f, 0.0f, -1.0f);
	vec3 y_vec = vec3(0.0f, 1.0f, 0.0f);
	mat4 matrix = mat4(1.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed;
	float sensitivity;

	Camera(int i_width, int i_height, vec3 i_position);

	void f_update(float FOVdeg, float nearPlane, float farPlane);
	void f_bind(Shader& shader, const char* uniform);
	void f_inputHandler(GLFWwindow* window);
};