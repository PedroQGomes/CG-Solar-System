#pragma once


typedef struct Vertex {
	float x;
	float y;
	float z;
} vertex;


vertex newVertex(float x1, float y1, float z1);

vertex newVertex(vertex v1);