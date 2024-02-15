#ifndef OPENGL_TEST_CUSTOM_DRAW_H
#define OPENGL_TEST_CUSTOM_DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int drawTriangle(void);
int drawCircle(unsigned int shaderProgram, unsigned int numTriangles, unsigned int wireframe);

#endif