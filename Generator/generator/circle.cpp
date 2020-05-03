#include <cmath>
#include "circle.h"


int circle(float radius, int slices, std::string file) {

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

