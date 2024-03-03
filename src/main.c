#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "custom/init.h"
#include "custom/shader.h"
#include "custom/draw.h"
#include "custom/status.h"


/**************************************************************************************************/
int main(void) 
{
	GLFWwindow *window;
	unsigned int shaderProgram;

	if (createWindow(&window) != 0) {
		exit(EXIT_FAILURE);
	}
	if (initShaderProgram(&shaderProgram) != 0) {
		exit(EXIT_FAILURE);
	}
	setupProjectionMatrix(shaderProgram);
	programStatus.shaderProgram = shaderProgram;

	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		drawCircle(shaderProgram, 45, (float)programStatus.windowWidth / 2, 
							(float)programStatus.windowHeight / 2, 100, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}