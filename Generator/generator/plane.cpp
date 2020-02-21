#include <stdio.h>
#include <stdlib.h>
#include "write.h"


int plane(float size, char* file) {

	FILE * f = openFile(file);
	float x, z;
	
	x = size / 2;
	z = size / 2;

	printf("Writting\n");
	//1º Triângulo
	writeVertexToF(-x, 0.0, z, f);
	writeVertexToF( x, 0.0, z, f);
	writeVertexToF( x, 0.0,-z, f);

	//2º Triângulo
	writeVertexToF( x, 0.0,-z, f);
	writeVertexToF(-x, 0.0,-z, f);
	writeVertexToF(-x, 0.0, z, f);

	return 1;
}