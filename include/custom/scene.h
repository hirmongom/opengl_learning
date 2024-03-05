#ifndef OPENGL_TEST_CUSTOM_SCENE_H
#define OPENGL_TEST_CUSTOM_SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "custom/draw.h"
#include "custom/status.h"

#define MAX_SCENE_SIZE 1024

int initScene(void);
int renderScene(void);
int addObjectToScene(unsigned int *VAO, unsigned int triangleCount);
// int clearScene();

#endif