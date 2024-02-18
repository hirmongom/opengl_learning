#include "custom/init.h"


/**************************************************************************************************/
ProgramStatus programStatus = {
	1920,					/* Window Width */
	1080,					/* Window Height */
	0,						/* Shader Program */
};


/**************************************************************************************************/
static void errorCallback(int error, const char* description) 
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}


/**************************************************************************************************/
static void framebufferSizeCallback(UNUSED GLFWwindow *window, int width, int height) 
{
	programStatus.windowWidth = width;
	programStatus.windowHeight = height;
	glViewport(0, 0, width, height);
}


/**************************************************************************************************/
static void keyCallback(GLFWwindow* window, int key, UNUSED int scancode, int action, 
UNUSED int mods) 
{
	switch(key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS)
				escKeyPress(window);
			break;
		
		default:
			break;
	}
}


/**************************************************************************************************/
static void mouseButtonCallback(GLFWwindow* window, int button, int action, UNUSED int mods) 
{
	if (action == GLFW_PRESS) {
		switch(button) {
			case GLFW_MOUSE_BUTTON_LEFT:
				leftMouseButtonPress(window);
				break;
			
			default:
				break;
		}
	}
}


/**************************************************************************************************/
int createWindow(GLFWwindow **window, int width, int height) 
{
	if (glfwInit() == GLFW_FALSE) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	programStatus.windowWidth = width;
	programStatus.windowHeight = height;

	*window = glfwCreateWindow(width, height, "OpenGL Test", NULL, NULL);
	if (!(*window)) {
		fprintf(stderr, "Failed to create window\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(*window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, width, height);
	
	glfwSetErrorCallback(errorCallback);
	glfwSetFramebufferSizeCallback(*window, framebufferSizeCallback);
	glfwSetKeyCallback(*window, keyCallback);
	glfwSetMouseButtonCallback(*window, mouseButtonCallback);

	return 0;
}