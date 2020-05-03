#include "sphere.h"
#include <cmath>

int sphere(float radius, int slices, int stacks, std::string file) {

	std::ofstream f;
	f.open(file);
	float x1,x2,z1,z2,y1,y2, h1,h2;
	float angleH = (2 * PI) / slices;
	float angleV = PI / stacks;
	float stackHeight = radius*2/stacks;
	
	for (float i = 0; i < stacks; i++) {
		h1 = sin(angleV * i);
		h2 = sin(angleV * (i + 1));
		for (int j = 0; j < slices; j++) {

			x1 = radius * cos(angleH * j);
			z1 = radius * sin(angleH * j);
			x2 = radius * cos(angleH * (j + 1));
			z2 = radius * sin(angleH * (j + 1));

			y1 = radius * sin((-PI/2) + angleV * i);
			y2 = radius * sin((-PI/2) + angleV *(i + 1));

			writePointToF(x1 * h1, y1, z1 * h1, f);
			writePointToF(x1 * h2, y2, z1 * h2, f);
			writePointToF(x2 * h1, y1, z2 * h1, f);

			writePointToF(x1 * h2, y2, z1 * h2, f);
			writePointToF(x2 * h2, y2, z2 * h2, f);
			writePointToF(x2 * h1, y1, z2 * h1, f);
		}
	}


	return 1;



}
