#pragma once


struct vertex {
	float x;
	float y;
	float z;
};
typedef struct vertex* Vertex;

Vertex newVertex(float x1, float y1, float z1);
