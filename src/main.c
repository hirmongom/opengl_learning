#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "custom/init.h"
#include "custom/shader.h"
#include "custom/draw.h"

#define 	WINDOW_WIDTH 		1920
#define 	WINDOW_HEIGHT 	1080


/**************************************************************************************************/
int main(void) 
{
	GLFWwindow *window;
	unsigned int shaderProgram;

	if (createWindow(&window, WINDOW_WIDTH, WINDOW_HEIGHT) != 0) {
		exit(EXIT_FAILURE);
	} 
	if (initShaderProgram(&shaderProgram) != 0) {
		exit(EXIT_FAILURE);
	}
	setupProjectionMatrix(shaderProgram, WINDOW_WIDTH, WINDOW_HEIGHT);


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawCircle(shaderProgram, 45, (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2, 100, 1);

	while(!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}