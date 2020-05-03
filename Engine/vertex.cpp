#include "vertex.h"
#include <corecrt_malloc.h>


Vertex newVertex(float x1, float y1, float z1) {
    Vertex v = (Vertex)malloc(sizeof(struct vertex));
    if (!v)
        return NULL;
    v->x = x1;
    v->y = y1; 
    v->z = z1;
    return v;
}

/*
Vertex newVertex(Vertex v1){

	Vertex v = new Vertex(v1.x, v1.y, v1.z);
	return v;
}*/
