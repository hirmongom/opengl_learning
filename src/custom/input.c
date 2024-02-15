#include "custom/input.h"

/**************************************************************************************************/
void leftMouseButtonPress(GLFWwindow *window) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	fprintf(stdout, "Left mouse button clicked at (%f, %f)\n", xpos, ypos);
}


/**************************************************************************************************/
void escKeyPress(GLFWwindow *window) {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}