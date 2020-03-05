#include "plane.h"

using namespace std;


int plane(float size, std::string file) {

	std::ofstream f;
	f.open(file);
	float x, z;
	
	x = size / 2;
	z = size / 2;

	printf("Writting\n");
	//10 Triangulo
	writeVertexToF(-x, 0.0, z, f);
	writeVertexToF( x, 0.0, z, f);
	writeVertexToF( x, 0.0,-z, f);

	//20 Triangulo
	writeVertexToF( x, 0.0,-z, f);
	writeVertexToF(-x, 0.0,-z, f);
	writeVertexToF(-x, 0.0, z, f);

	return 1;
}