#include"Model.h"

unsigned int width = 1920;
unsigned int height = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glViewport(0, 0, width, height);

	Shader shaderProgram("./res/shaders/default.vert", "./res/shaders/default.frag");
	shaderProgram.f_activate();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Camera camera(width, height, vec3(0.0f, 0.8f, 3.0f));
	Model trees("./res/koharu.gltf");

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			return 0;

		camera.f_inputHandler(window);
		camera.f_update(45.0f, 0.1f, 100.0f);

		trees.f_render(shaderProgram, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.f_delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}