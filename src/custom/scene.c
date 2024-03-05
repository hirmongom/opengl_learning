#include "custom/scene.h"


/**************************************************************************************************/
typedef struct {
	unsigned int triangleCount;
	unsigned int *VAO;
} Object;

typedef struct {
	size_t size;
	Object *objects[MAX_SCENE_SIZE];
} Scene;


/**************************************************************************************************/
static Scene *scene;


/**************************************************************************************************/
int initScene(void)
{
	scene = (Scene*)malloc(sizeof(Scene));
	if (!scene) {
		fprintf(stderr, "Error: Failed to allocate memory for Scene\n");
		return 1;
	}
	scene->size = 0;

	return 0;
}


/**************************************************************************************************/
int renderScene(void)
{
	for (size_t i = 0; i < scene->size; i++) {
		drawObject(programStatus.shaderProgram, scene->objects[i]->VAO,
								scene->objects[i]->triangleCount, 0);
	}
	return 0;
}


/**************************************************************************************************/
int addObjectToScene(unsigned int *VAO, unsigned int triangleCount)
{
	Object *object = (Object*)malloc(sizeof(Object));
	object->VAO = VAO;
	object->triangleCount = triangleCount;

	if (scene->size != MAX_SCENE_SIZE) {
		scene->objects[scene->size] = object;
		scene->size++;
		return 0;
	}
	else {
		fprintf(stderr, "Error: Scene is at max capacity\n");
		return 1;
	}
}