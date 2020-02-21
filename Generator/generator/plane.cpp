#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "write.h"

using namespace std;


int plane(float size, std::string file) {

	std::ofstream f;
	f.open(file);
	float x, z;
	
	x = size / 2;
	z = size / 2;

	printf("Writting\n");
	//1� Tri�ngulo
	writeVertexToF(-x, 0.0, z, f);
	writeVertexToF( x, 0.0, z, f);
	writeVertexToF( x, 0.0,-z, f);

	//2� Tri�ngulo
	writeVertexToF( x, 0.0,-z, f);
	writeVertexToF(-x, 0.0,-z, f);
	writeVertexToF(-x, 0.0, z, f);

	return 1;
}