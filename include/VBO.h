#pragma once

#include "Include.h"

struct Vertex {
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texUV;
};

struct VBO {
	GLuint ID;

	VBO(vector<Vertex>& vertices);

	void f_bind();
	void f_unbind();
	void f_delete();
};