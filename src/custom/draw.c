#include "custom/draw.h"


/**************************************************************************************************/
static int generateCircleVertices(float** vertices, unsigned int **indices, 
size_t *outVerticesSize, size_t *outIndicesSize, unsigned int triangleCount, 
unsigned int posX, unsigned int posY, float radius) 
{
	float angle = 2 * M_PI / triangleCount;

	*outVerticesSize = (triangleCount + 1) * 3 * sizeof(float);
	*outIndicesSize = (triangleCount + 1) * 3 * sizeof(unsigned int);
	*vertices = (float*)malloc(*outVerticesSize);
	*indices = (unsigned int*)malloc(*outIndicesSize);

	/* Center of the Circle */
	(*vertices)[0] = posX;
	(*vertices)[1] = posY;
	(*vertices)[2] = 0;

	for (unsigned int i = 1; i <= triangleCount; i++) {
		float currAngle = angle * (i - 1);
		float x = posX + radius * cos(currAngle);
		float y = posY + radius * sin(currAngle);
		float z = 0.0f;

		(*vertices)[i * 3] = x;
		(*vertices)[i * 3 + 1] = y;
		(*vertices)[i * 3 + 2] = z;

		(*indices)[(i - 1) * 3] = 0;
		(*indices)[(i - 1) * 3 + 1] = i;
		(*indices)[(i - 1) * 3 + 2] = i + 1;
	}
	(*indices)[triangleCount * 3 - 1] = 1; /* Join last triangle with the first one */

	return 0;
}


/**************************************************************************************************/
int drawCircle(unsigned int shaderProgram, unsigned int numTriangles, 
unsigned int posX, unsigned int posY, float radius, 
unsigned int wireframe) 
{
	fprintf(stdout, "Drawing on %d * %d\n", posX, posY);
	unsigned int VAO, VBO, EBO;
	float *vertices;
	unsigned int *indices;
	size_t verticesSize, indicesSize;

	/* For later use */
	if (numTriangles % 3 != 0) {
		fprintf(stderr, "Error: Invalid number of triangles\n");
		return 1;
	}

	generateCircleVertices(&vertices, &indices, &verticesSize, &indicesSize, numTriangles, 
													posX, posY, radius);

	/* Debug: */
	// printf("float vertices[] = {\n");
	// for (unsigned int i = 0; i <= numTriangles; i++) {
	// 	printf("\t%f, %f, %f,\n", vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
	// }
	// printf("};\n");

	// printf("unsigned int indices[] = {\n");
	// for (unsigned int i = 0; i < numTriangles * 3; i += 3) {
	// 	printf("\t%d, %d, %d,\n", indices[i], indices[i + 1], indices[i + 2]);
	// }
	// printf("};\n");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* Draw */
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numTriangles * 3, GL_UNSIGNED_INT, 0);

	/* Clear */
	free(vertices);
	free(indices);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}