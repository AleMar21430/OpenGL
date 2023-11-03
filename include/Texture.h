#pragma once

#include "Include.h"

#include "Shader_Program.h"

#include "stb_image.h"

struct Image {
	uint16_t width;
	uint16_t height;
	unsigned char* data;
	int channel_fromat;
	int data_type;

	Image();
	bool f_load(const string& i_file_path);
};

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