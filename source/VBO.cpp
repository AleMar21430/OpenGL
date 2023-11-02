#include"VBO.h"

VBO::VBO(std::vector<Vertex>& vertices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::f_bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::f_unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::f_delete() {
	glDeleteBuffers(1, &ID);
}