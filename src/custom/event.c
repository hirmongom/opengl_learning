#include "custom/event.h"

/**************************************************************************************************/
inline void windowResize() 
{
	setupProjectionMatrix(programStatus.shaderProgram, programStatus.windowWidth, 
												programStatus.windowHeight);
}


/**************************************************************************************************/
inline void leftMouseButtonPress(GLFWwindow *window) 
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	fprintf(stdout, "Left mouse button clicked at (%f, %f)\n", xpos, ypos);
}


/**************************************************************************************************/
inline void escKeyPress(GLFWwindow *window) 
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}