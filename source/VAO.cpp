#include"VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::f_linkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.f_bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.f_unbind();
}

void VAO::f_bind() {
	glBindVertexArray(ID);
}

void VAO::f_unbind() {
	glBindVertexArray(0);
}

void VAO::f_delete() {
	glDeleteVertexArrays(1, &ID);
}