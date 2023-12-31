#include"Texture.h"

Image::Image() {}

bool Image::f_load(const string& i_file_path) {
	int t_width, t_height, t_nrChannels;
	data = stbi_load(i_file_path.c_str(), &t_width, &t_height, &t_nrChannels, 0);
	if (data) {
		if (t_nrChannels == 1)
			channel_fromat = GL_RED;
		else if (t_nrChannels == 3)
			channel_fromat = GL_RGB;
		else if (t_nrChannels == 4)
			channel_fromat = GL_RGBA;
		width = t_width;
		height = t_height;
		data_type = GL_UNSIGNED_BYTE;
		return true;
	}
	return false;
}

Texture::Texture(const char* image, const char* texType, GLuint slot) {
	type = texType;
	opengl_texture_unit = slot;

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (numColCh == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	else
		throw invalid_argument("Automatic Texture type recognition failed");

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::f_activate(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.f_activate();
	glUniform1i(texUni, unit);
}

void Texture::f_bind() {
	glActiveTexture(GL_TEXTURE0 + opengl_texture_unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::f_unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::f_delete() {
	glDeleteTextures(1, &ID);
}