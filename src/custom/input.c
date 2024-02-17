#include "custom/input.h"

/**************************************************************************************************/
inline void leftMouseButtonPress(GLFWwindow *window) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	fprintf(stdout, "Left mouse button clicked at (%f, %f)\n", xpos, ypos);
}


/**************************************************************************************************/
inline void escKeyPress(GLFWwindow *window) {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}