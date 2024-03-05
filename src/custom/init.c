#include "custom/init.h"


/**************************************************************************************************/
ProgramStatus programStatus = {
	0,						/* Window Width */
	0,						/* Window Height */
	0,						/* Shader Program */
};

static GLFWmonitor *monitor;
static const GLFWvidmode *mode;


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
int createWindow(GLFWwindow **window) 
{
	if (glfwInit() == GLFW_FALSE) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);
	
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	
	*window = glfwCreateWindow(mode->width, mode->height, "OpenGL Test", monitor, NULL);
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

	programStatus.windowWidth = mode->width;
	programStatus.windowHeight = mode->height;

	glViewport(0, 0, mode->width, mode->height);
	
	glfwSetErrorCallback(errorCallback);
	glfwSetFramebufferSizeCallback(*window, framebufferSizeCallback);
	glfwSetKeyCallback(*window, keyCallback);
	glfwSetMouseButtonCallback(*window, mouseButtonCallback);

	if (initScene() != 0) {
		fprintf(stderr, "Error: Failed to initialize scene\n");
		return 1;
	};

	const char *version = glfwGetVersionString();
	fprintf(stdout, "Using OpenGL version %s\n", version);

	return 0;
}