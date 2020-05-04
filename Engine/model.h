#pragma once
#include "headers.h"
#include "vertex.h"
#include <GL\glcorearb.h>

typedef struct Model {
	std::vector<float> vertexes;
	std::vector<unsigned int> indices;
	GLuint vBuff[1];
	GLuint iBuff[1];
} model;

void addVertex(model * m, float f);

float getVertex(model * m, int i);

int getSize(model m);

void drawModel(model * m);
void fillBuffers(model * m);
	
