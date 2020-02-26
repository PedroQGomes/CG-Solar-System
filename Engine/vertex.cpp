#include "vertex.h"


vertex newVertex(float x1, float y1, float z1) {
	vertex v;
	v.x = x1;
	v.y = y1;
	v.z = z1;
	return v;
}

vertex newVertex(vertex v1){

	vertex v;
	v.x = v1.x;
	v.y = v1.y;
	v.z = v1.z;
	return v;
}
