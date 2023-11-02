#pragma once

#include "Include.h"

struct EBO {
	GLuint ID;

	EBO(vector<GLuint>& indices);

	void f_bind();
	void f_unbind();
	void f_delete();
};