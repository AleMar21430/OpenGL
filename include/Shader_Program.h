#pragma once

#include "Include.h"

struct Shader {
	GLuint ID;

	Shader(const char* vertexFile, const char* fragmentFile);

	void f_activate();
	void f_delete();
	void f_compilationCheck(unsigned int shader, const char* type);
};