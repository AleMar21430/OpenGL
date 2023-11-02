#pragma once

#include "Include.h"

#include "Mesh.h"

struct Model {
	const char* file;
	vector<unsigned char> data;
	json JSON;

	vector<Mesh> meshes;
	vector<vec3> positions;
	vector<quat> rotations;
	vector<vec3> scales;
	vector<mat4> matrices;

	vector<string> texture_names;
	vector<Texture> textures;

	Model(const char* i_file);

	void f_render(Shader& shader, Camera& camera);
	void f_loadMesh(unsigned int indMesh);
	void f_traverseGLTF(unsigned int nextNode, mat4 matrix = mat4(1.0f));

	vector<unsigned char> getData();
	vector<float> getFloats(json accessor);
	vector<GLuint> getIndices(json accessor);
	vector<Texture> getTextures();

	vector<Vertex> assembleVertices (
		vector<vec3> positions,
		vector<vec3> normals,
		vector<vec2> texUVs
	);
};