#pragma once
#include "headers.h"
#include "vertex.h"

typedef struct Model {
	std::vector<vertex> vertexes;
	std::vector<unsigned int> indices;
	//GLuint vBuff[1];
	//GLuint iBuff[1];
} model;

void addVertex(model * m, vertex v);

vertex getVertex(model * m, int i);

int getSize(model m);

void drawModel(model m);
	
