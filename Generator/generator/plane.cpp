#include "plane.h"

using namespace std;


int plane(float size, std::string file) {

	std::ofstream f;
	f.open(file);
	float x, z;
	
	x = size / 2;
	z = size / 2;

	printf("Writting\n");
	writePointToF(x, 0, z, f);
	writePointToF(-x, 0, -z, f);
	writePointToF(-x, 0, z, f);
	writePointToF(x, 0, -z, f);

	writeIntToFile(0, f);
	writeIntToFile(1, f);
	writeIntToFile(2, f);
	writeIntToFile(1, f);
	writeIntToFile(0, f);
	writeIntToFile(3, f);


	writePointToF(0.0f, 1.0f, 0.0f, f);
	writePointToF(0.0f, 1.0f, 0.0f, f);
	writePointToF(0.0f, 1.0f, 0.0f, f);
	writePointToF(0.0f, 1.0f, 0.0f, f);

	write2IntToFile(1.0f, 1.0f, f);
	write2IntToFile(0.0f, 0.0f, f);
	write2IntToFile(0.0f, 1.0f, f);
	write2IntToFile(1.0f, 0.0f, f);

	return 1;
}