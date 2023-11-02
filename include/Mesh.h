#pragma once

#include "Include.h"

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

struct Mesh {
	vector <Vertex>  vertices;
	vector <GLuint>  indices;
	vector <Texture> textures;

	VAO VAO;

	Mesh(vector <Vertex>& vertices, vector <GLuint>& indices, vector <Texture>& textures);

	void f_render (
		Shader& shader,
		Camera& camera,
		mat4 matrix = mat4(1.0f),
		vec3 translation = vec3(0.0f, 0.0f, 0.0f),
		quat rotation = quat(1.0f, 0.0f, 0.0f, 0.0f),
		vec3 scale = vec3(1.0f, 1.0f, 1.0f)
	);
};