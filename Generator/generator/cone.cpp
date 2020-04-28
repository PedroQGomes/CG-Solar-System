#include <cmath>
#include "cone.h"

int cone(float radius, float height, int slices, int stacks, std::string file) {

	coneBottomCircle(radius, slices, file);
	coneUpperBody(radius, height, slices, stacks, file);

	return 1;
}


int coneBottomCircle(float radius, int slices, std::string file) {

	std::ofstream f;
	f.open(file);

	float angle = (2 * PI) / slices;
	float x1, z1, x2, z2;

	for (int i = 0; i < slices; i++) {

		x1 = radius * cos(angle * i);
		z1 = radius * sin(angle * i);
		x2 = radius * cos(angle * (i + 1));
		z2 = radius * sin(angle * (i + 1));
		
		writeVertexToF(0.0, 0.0, 0.0, f);
		writeVertexToF(x1, 0.0, z1, f);
		writeVertexToF(x2, 0.0, z2, f);		
	}

	f.close();

	return 0;
}

int coneUpperBody(float radius, float height, int slices, int stacks, std::string file){

	std::ofstream f;
	f.open(file);
	float x1, x2, z1, z2, h1, h2;
	float angleH = (2 * PI) / slices; //angulo horizontal entre a origem e o ponto
	//float angleV = PI / (2*stacks); //�ngulo vertical entre a origem e o ponto
	float stackHeight = height / stacks;

	for (float i = 0; i < stacks; i++) {
		h1 = (1-(i/stacks));
		h2 = (1-(i+1)/stacks);
		printf("h1:%f\n",h1);
		printf("h2:%f\n",h2);
		printf("stacks:%d, i:%d\n", stacks, i);
		for (int j = 0; j < slices; j++) {

			x1 = radius * cos(angleH * j);
			z1 = radius * sin(angleH * j);
			x2 = radius * cos(angleH * (j + 1));
			z2 = radius * sin(angleH * (j + 1));

			writeVertexToF(x1 * h1, stackHeight * i,	z1 * h1, f);
			writeVertexToF(x1 * h2, stackHeight * (i+1), z1 * h2, f);
			writeVertexToF(x2 * h1, stackHeight * i,	z2 * h1, f);

			writeVertexToF(x1 * h2, stackHeight * (i+1), z1 * h2, f);
			writeVertexToF(x2 * h2, stackHeight * (i+1), z2 * h2, f);
			writeVertexToF(x2 * h1, stackHeight * i, z2 * h1, f);
		}
	}


	return 1;
}