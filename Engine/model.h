#pragma once
#include "headers.h"
#include "vertex.h"

typedef struct Model {
	std::vector<vertex> vertexes;
} model;

void addVertex(model * m, vertex v);

vertex getVertex(model * m, int i);

int getSize(model m);

void drawModel(model m);
	
