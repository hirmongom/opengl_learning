#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "custom/draw.h"
#include "custom/init.h"
#include "custom/scene.h"
#include "custom/shader.h"
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
	programStatus.shaderProgram = &shaderProgram;

	unsigned int VAO1, VAO2;
	createCircle(21, 1000, 1000, 100, &VAO1);
	createCircle(21, 2000, 1500, 200, &VAO2);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		renderScene();
		drawObject(&shaderProgram, &VAO1, 21, 0);
		drawObject(&shaderProgram, &VAO2, 21, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}