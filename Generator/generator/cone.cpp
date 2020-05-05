#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <vector>
#include "cone.h"


int coneVBO(float radius, float height, int slices, int stacks, std::string file) {
	std::ofstream f(file);


	if(slices < 0 || stacks < 0)
	return 1;

	float angle = (float) (2 * M_PI) / slices;
	float division = height / stacks;
	float baseY = height / 2;
	writePointToF(0.0f, 0.0f - baseY, 0.0f, f);
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j < stacks + 1; j++) {
			float div = (float) j / stacks;
			float radiusD = (float) ((1.0 - div)) * radius;
			
			// Triangulo [x1,z1,y]
			float x1 = radiusD * cos(i * angle);
			float y1 = j * division - baseY;
			float z1 = radiusD * sin(i * angle);
			writePointToF(x1, y1, z1, f);
		}
	}

	int a1,a2,a3,i1, i2, i3, i4, k;
	int auxstacks = stacks + 1;

	for (int i = 0; i < auxstacks; i++) {
		if (i == slices)
			k = 0;
		else k = i;

		writeIntToFile(0, f);
		writeIntToFile(auxstacks * k + 1, f);
		writeIntToFile(auxstacks * (k + 1) + 1, f);

		for (int j = 1; j < auxstacks; j++) {
			i1 = auxstacks * k + j;
			i2 = auxstacks * k + j + 1;
			i3 = auxstacks * (k + 1) + j;
			i4 = auxstacks * (k + 1) + j + 1;

			writeIntToFile(i1, f);
			writeIntToFile(i2, f);
			writeIntToFile(i3, f);
			writeIntToFile(i3, f);
			writeIntToFile(i2, f);
			writeIntToFile(i4, f);
		}
	}
	

	return 0;
}

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
		
		writePointToF(0.0, 0.0, 0.0, f);
		writePointToF(x1, 0.0, z1, f);
		writePointToF(x2, 0.0, z2, f);
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

			writePointToF(x1 * h1, stackHeight * i,	z1 * h1, f);
			writePointToF(x1 * h2, stackHeight * (i+1), z1 * h2, f);
			writePointToF(x2 * h1, stackHeight * i,	z2 * h1, f);

			writePointToF(x1 * h2, stackHeight * (i+1), z1 * h2, f);
			writePointToF(x2 * h2, stackHeight * (i+1), z2 * h2, f);
			writePointToF(x2 * h1, stackHeight * i, z2 * h1, f);
		}
	}


	return 1;
}


