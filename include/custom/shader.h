#ifndef OPENGL_TEST_CUSTOM_SHADER_H
#define OPENGL_TEST_CUSTOM_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "custom/status.h"

int initShaderProgram(unsigned int *shaderProgram);
int setupProjectionMatrix(unsigned int shaderProgram);

#endif