#include "custom/shader.h"


/**************************************************************************************************/
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"uniform mat4 projection;\n"
	"void main() {\n"
	"	gl_Position = projection * vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";


/**************************************************************************************************/
const char *fragmentShaderSource= "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";


/**************************************************************************************************/
int initShaderProgram(unsigned int *shaderProgram) 
{
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


/**************************************************************************************************/
int setupProjectionMatrix(unsigned int shaderProgram, int width, int height) 
{
	glUseProgram(shaderProgram);
	
	float left = 0.0f;
	float right = (float)width;
	float bottom = 0.0f;
	float top = (float)height;

	float projectionMatrix[16] = {
		// Scale factors for x, y, and z axes (right - left), (top - bottom), and z-axis clipping planes
		2.0f / (right - left), 0.0f, 0.0f, 0.0f,
		
		// No skewing for the x-axis, scale factor for y-axis, and clipping planes for the z-axis
		0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
		
		// No scaling or skewing for the z-axis, but set near clipping plane to -1
		0.0f, 0.0f, -1.0f, 0.0f,
		
		// Translation factors for the x and y axes, set z-axis clipping planes, and set w-axis
		-(right + left) / (right - left), -(top + bottom) / (top - bottom), 0.0f, 1.0f
	};

	int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);

	return 0;
}