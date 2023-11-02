#include "Mesh.h"

Mesh::Mesh(vector <Vertex>& vertices, vector <GLuint>& indices, vector <Texture>& textures) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.f_bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	VAO.f_linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.f_linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.f_linkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.f_linkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	VAO.f_unbind();
	VBO.f_unbind();
	EBO.f_unbind();
}

void Mesh::f_render (Shader& shader, Camera& camera, mat4 matrix, vec3 translation, quat rotation, vec3 scale) {
	shader.f_activate();
	VAO.f_bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++) {
		string num;
		string type = textures[i].type;
		if (type == "diffuse")
			num = to_string(numDiffuse++);
		else if (type == "specular")
			num = to_string(numSpecular++);

		textures[i].f_activate(shader, (type + num).c_str(), i);
		textures[i].f_bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
	camera.f_bind(shader, "camMatrix");

	mat4 trans = mat4(1.0f);
	mat4 rot = mat4(1.0f);
	mat4 sca = mat4(1.0f);

	trans = translate(trans, translation);
	rot = mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, value_ptr(matrix));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}