#pragma once

#include "Include.h"

#include "Shader_Program.h"

#include "stb_image.h"

struct Texture {
	GLuint ID;

	GLuint opengl_texture_unit;
	const char* type;

	Texture(const char* image, const char* texType, GLuint slot);

	void f_activate(Shader& shader, const char* uniform, GLuint unit);
	void f_bind();
	void f_unbind();
	void f_delete();
};