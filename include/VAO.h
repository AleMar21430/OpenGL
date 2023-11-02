#pragma once

#include "Include.h"

#include"VBO.h"

struct VAO {
	GLuint ID;

	VAO();

	void f_linkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void f_bind();
	void f_unbind();
	void f_delete();
};