#include "custom/shader.h"


/**************************************************************************************************/
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main() {\n"
	"	gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";


/**************************************************************************************************/
const char *fragmentShaderSource= "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";


/**************************************************************************************************/
int initShaderProgram(unsigned int *shaderProgram) {
	int status;
	char log[512];
	unsigned int vertexShader;
	unsigned int fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (!status) {
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		fprintf(stderr, "Error: Vertex Shader Compilation Failed:\n%s", log);
		return 1;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (!status) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		fprintf(stderr, "Error: Fragment Shader Compilation Failed:\n%s", log);
		return 1;
	}

	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &status);
	if (!status) {
		glGetProgramInfoLog(*shaderProgram, 512, NULL, log);
		fprintf(stderr, "Error: Failded to link Shader Program:\n%s", log);
		return 1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return 0;
}