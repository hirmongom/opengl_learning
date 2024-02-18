#ifndef OPENGL_TEST_CUSTOM_EVENT_H
#define OPENGL_TEST_CUSTOM_EVENT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "custom/shader.h"
#include "custom/status.h"

void windowResize();
void leftMouseButtonPress(GLFWwindow *window);
void escKeyPress(GLFWwindow *window);

#endif