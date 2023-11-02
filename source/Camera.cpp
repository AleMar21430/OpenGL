#include"Camera.h"

Camera::Camera(int i_width, int i_height, vec3 i_position) {
	width = i_width;
	height = i_height;
	position = i_position;
	speed = 0.01f;
	sensitivity = 100.0f;
}

void Camera::f_update(float FOVdeg, float nearPlane, float farPlane) {
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	view = lookAt(position, position + z_vec, y_vec);
	projection = perspective(radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	matrix = projection * view;
}

void Camera::f_bind(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, value_ptr(matrix));
}

void Camera::f_inputHandler(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += speed * z_vec;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position += speed * -normalize(cross(z_vec, y_vec));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position += speed * -z_vec;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += speed * normalize(cross(z_vec, y_vec));
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS))
		position += speed * y_vec;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS))
		position += speed * -y_vec;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 0.01f;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		vec3 newOrientation = rotate(z_vec, radians(-rotX), normalize(cross(z_vec, y_vec)));

		if (abs(angle(newOrientation, y_vec) - radians(90.0f)) <= radians(85.0f))
			z_vec = newOrientation;

		z_vec = rotate(z_vec, radians(-rotY), y_vec);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}