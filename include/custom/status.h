#ifndef OPENGL_TEST_CUSTOM_STATUS_H
#define OPENGL_TEST_CUSTOM_STATUS_H

typedef struct {
	int windowWidth;
	int windowHeight;
	unsigned int shaderProgram;
} ProgramStatus;

extern ProgramStatus programStatus;

#endif