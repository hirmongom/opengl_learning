#ifndef OPENGL_TEST_CUSTOM_DRAW_H
#define OPENGL_TEST_CUSTOM_DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "status.h"

int createCircle(unsigned int triangleCount, unsigned int posX, unsigned int posY,
								unsigned int radius, unsigned int *outVAO);
int drawObject(unsigned int *shaderProgram, unsigned int *VAO, unsigned int triangleCount,
							unsigned int wireframe);

#endif