#include "custom/event.h"


/**************************************************************************************************/
inline void windowResize() 
{
	setupProjectionMatrix(*programStatus.shaderProgram);
}


/**************************************************************************************************/
inline void leftMouseButtonPress(GLFWwindow *window) 
{
	unsigned int triangleCount = 21;
	unsigned int radius = 100;
	unsigned int VAO;
	double posX, posY;

	glfwGetCursorPos(window, &posX, &posY);
	fprintf(stdout, "Left mouse button clicked at (%f, %f)\n", posX, posY);

	createCircle(triangleCount, posX, posY, radius, &VAO);
	addObjectToScene(&VAO, triangleCount);
}


/**************************************************************************************************/
inline void escKeyPress(GLFWwindow *window) 
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}